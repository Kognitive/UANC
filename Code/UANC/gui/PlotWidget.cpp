//
// Created by jannewulf on 12.12.16.
//

#include <Code/UANC/amv/InvertedModel.h>
#include "PlotWidget.h"

namespace uanc {
namespace gui {

PlotWidget::PlotWidget() : EventObserver({Events::Scroll}) {
  this->initialize();
}

void PlotWidget::initialize() {
  // create the signal plot and the control plot
  std::shared_ptr<PlotWidget> sharedThis = std::shared_ptr<PlotWidget>(this);
  _signalPlot = std::shared_ptr<SignalPlot>(new SignalPlot(sharedThis));
  _control = std::shared_ptr<Control>(new Control(sharedThis));
  _chkBoxShowError = std::shared_ptr<QCheckBox>(new QCheckBox("Show Error"));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%m:%s:%z");
  _signalPlot->xAxis->setTicker(timeTicker);

  // update plot when state of checkbox changes
  connect(_chkBoxShowError.get(), SIGNAL(toggled(bool)), _signalPlot.get(), SLOT(hideError(bool)));

  // set size policy, such that control has minimum height
  _control->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  // create the layout
  _layout = new QVBoxLayout;
  _layout->addWidget(_signalPlot.get());
  _layout->addWidget(_control.get());
  setLayout(_layout);
}

void PlotWidget::setSignal(std::shared_ptr<uanc::amv::InvertedModel> signal) {
  // save pointer to signal in member
  _signal = signal;
  if (signal->inverted && !_chkShown)
    _layout->addWidget(_chkBoxShowError.get());

  if (signal->inverted) {
    _signal = signal->inverted;
    _errorSignal = std::shared_ptr<uanc::amv::InvertedModel>(new uanc::amv::InvertedModel);
    _errorSignal->left_channel = std::shared_ptr<Aquila::SignalSource>(new Aquila::SignalSource(*signal->left_channel + *signal->inverted->left_channel));
    _errorSignal->right_channel = std::shared_ptr<Aquila::SignalSource>(new Aquila::SignalSource(*signal->right_channel + *signal->inverted->right_channel));
  }

  // create QCPGraphDataContainer and set data in both graphs
  // creating two maps because QCustomPlot requires raw pointers and we want to prevent null pointers
  double maxSignalAmplitude = std::numeric_limits<double>::min();
  double minSignalAmplitude = std::numeric_limits<double>::max();
  size_t n = _signal->left_channel->getSamplesCount();
  QCPGraphDataContainer *newDataMain = new QCPGraphDataContainer;
  QCPGraphDataContainer *newDataControl = new QCPGraphDataContainer;
  QCPGraphDataContainer *newError = new QCPGraphDataContainer;
  QCPGraphData newDatapoint;

  double timeConversionFactor = 1.0 / _signal->left_channel->getSampleFrequency();
  _lastIndex = n / _signal->left_channel->getSampleFrequency();

  for (size_t i = 0; i < n; ++i) {
    newDatapoint.key = timeConversionFactor * i;
    newDatapoint.value = _signal->left_channel->sample(i);

    newDataMain->add(newDatapoint);
    newDataControl->add(newDatapoint);

    // keep track of max and min amplitude
    maxSignalAmplitude = std::max(maxSignalAmplitude, newDatapoint.value);
    minSignalAmplitude = std::min(minSignalAmplitude, newDatapoint.value);

    if (signal->inverted) {
      newDatapoint.value = _errorSignal->left_channel->sample(i);
      newError->add(newDatapoint);
    }
  }

  _signalPlot->setData(newDataMain);
  if (signal->inverted)
    _signalPlot->setError(newError);
  _control->setData(newDataControl, maxSignalAmplitude, minSignalAmplitude);

  _signalPlot->replot();
  _control->replot();
}

const QCPRange PlotWidget::getPlotXRange() const {
  return _signalPlot->xAxis->range();
}

void PlotWidget::plotChanged() {
  QCPRange range = getPlotXRange();
  _control->updateNavBox(range);

  // trigger observed plots to replot
  triggerConnectedWidgets(range);
}

void PlotWidget::controlChanged() {
  double left = _control->getBoxLeft();
  double right = _control->getBoxRight();
  _signalPlot->setRange(left, right);

  triggerConnectedWidgets(QCPRange(left, right));
}

void PlotWidget::triggered(Events event, EventContainer data) {
  double lower = std::stod(data.get("lower"));
  double upper = std::stod(data.get("upper"));
  _control->updateNavBox(QCPRange(lower, upper));
  _signalPlot->setRange(lower, upper);
}

void PlotWidget::triggerConnectedWidgets(QCPRange range) {
  EventContainer container = EventContainer();
  container.add("lower", std::to_string(range.lower));
  container.add("upper", std::to_string(range.upper));
  _token->trigger(Events::Scroll, container);
}

}
}