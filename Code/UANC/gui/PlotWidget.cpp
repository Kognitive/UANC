//
// Created by jannewulf on 12.12.16.
//

#include <Code/UANC/amv/InvertedModel.h>
#include <Code/UANC/util/GlobalSettings.h>
#include <Code/UANC/util/DialogUtil.h>
#include <Code/UANC/util/SignalFileActor.h>
#include "PlotWidget.h"

namespace uanc {
namespace gui {

PlotWidget::PlotWidget() : EventObserver({Events::Scroll, Events::ChangeChannel}) {
  this->initialize();
}

void PlotWidget::initialize() {
  // create the signal plot and the control plot
  _signalPlot = new SignalPlot(this);
  _control = new Control(this);
  _chkBoxShowError = new QCheckBox("Show Error");

  // create the save button
  _btnSaveSignal = new QPushButton("Save");

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%m:%s:%z");
  _signalPlot->xAxis->setTicker(timeTicker);

  // update plot when state of checkbox changes
  connect(_chkBoxShowError, SIGNAL(toggled(bool)), _signalPlot, SLOT(hideError(bool)));

  // save Signal when button is pressed
  connect(_btnSaveSignal, SIGNAL(pressed()), this, SLOT(saveSignal()));

  // set size policy, such that control has minimum height
  _control->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  // create the layout
  _layout = new QVBoxLayout;
  _layout->addWidget(_signalPlot);
  _layout->addWidget(_control);
  setLayout(_layout);
}

void PlotWidget::setSignal(std::shared_ptr<uanc::amv::InvertedModel> signal) {
  // save pointer to signal in member
  _signal = signal;
  if (signal->inverted && !_chkShown) {
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(_chkBoxShowError);
    hLayout->addWidget(_btnSaveSignal);
    QWidget *widget = new QWidget;
    widget->setLayout(hLayout);
    widget->setFixedHeight(40);
    _layout->addWidget(widget);
  }

  if (signal->inverted) {
    _errorSignal = std::shared_ptr<uanc::amv::InvertedModel>(new uanc::amv::InvertedModel);
    _errorSignal->left_channel = std::shared_ptr<Aquila::SignalSource>(new Aquila::SignalSource(*signal->left_channel + *signal->inverted->left_channel));
    _errorSignal->right_channel = std::shared_ptr<Aquila::SignalSource>(new Aquila::SignalSource(*signal->right_channel + *signal->inverted->right_channel));
  }

  int channel = 0;
  if (_token->hasLastEvent(Events::ChangeChannel)) {
    channel = atoi(_token->getLastEvent(Events::ChangeChannel).get("Index").c_str());
  }

  switchChannel(channel);
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
  if (event == Events::Scroll) {
    double lower = std::stod(data.get("lower"));
    double upper = std::stod(data.get("upper"));
    _control->updateNavBox(QCPRange(lower, upper));
    _signalPlot->setRange(lower, upper);
  }
  else if (event == Events::ChangeChannel) {
    int index = atoi(data.get("Index").c_str());
    switchChannel(index);
  }
}

void PlotWidget::triggerConnectedWidgets(QCPRange range) {
  EventContainer container = EventContainer();
  container.add("lower", std::to_string(range.lower));
  container.add("upper", std::to_string(range.upper));
  _token->trigger(Events::Scroll, container);
}

void PlotWidget::switchChannel(int channel) {

    std::shared_ptr<Aquila::SignalSource> signal;
    std::shared_ptr<Aquila::SignalSource> errorSignal;
    if (_signal->inverted) {
      if (channel == 0) {
        signal = _signal->inverted->left_channel;
        errorSignal = _errorSignal->left_channel;
      }
      else {
        signal = _signal->inverted->right_channel;
        errorSignal = _errorSignal->right_channel;
      }
    }
    else {
      if (channel == 0) {
        signal = _signal->left_channel;
      }
      else {
        signal = _signal->right_channel;
      }
    }

    // create QCPGraphDataContainer and set data in both graphs
    // creating two maps because QCustomPlot requires raw pointers and we want to prevent null pointers
    double maxSignalAmplitude = std::numeric_limits<double>::min();
    double minSignalAmplitude = std::numeric_limits<double>::max();
    size_t n = signal->getSamplesCount();
    QCPGraphDataContainer *newDataMain = new QCPGraphDataContainer;
    QCPGraphDataContainer *newDataControl = new QCPGraphDataContainer;
    QCPGraphDataContainer *newError = new QCPGraphDataContainer;
    QCPGraphData newDatapoint;

    double timeConversionFactor = 1.0 / signal->getSampleFrequency();
    _lastIndex = n / signal->getSampleFrequency();

    for (size_t i = 0; i < n; ++i) {
      newDatapoint.key = timeConversionFactor * i;
      newDatapoint.value = signal->sample(i);

      newDataMain->add(newDatapoint);
      newDataControl->add(newDatapoint);

      // keep track of max and min amplitude
      maxSignalAmplitude = std::max(maxSignalAmplitude, newDatapoint.value);
      minSignalAmplitude = std::min(minSignalAmplitude, newDatapoint.value);

      if (_signal->inverted) {
        newDatapoint.value = errorSignal->sample(i);
        newError->add(newDatapoint);
      }
    }

    _signalPlot->setData(newDataMain);
    _signalPlot->setCenteredYAxis(_centeredYAxis);
    if (_signal->inverted) {
      _signalPlot->setError(newError);
    }
    _control->setData(newDataControl, maxSignalAmplitude, minSignalAmplitude);


    if (_token->hasLastEvent(Events::Scroll)) {
      EventContainer container = _token->getLastEvent(Events::Scroll);
      double lower = std::stod(container.get("lower"));
      double upper = std::stod(container.get("upper"));
      _control->updateNavBox(QCPRange(lower, upper));
      _signalPlot->setRange(lower, upper);
    }
    else {
      _signalPlot->replot();
      _control->replot();
    }
}


void PlotWidget::saveSignal() {
  // get path to an saveable file
  util::DialogUtil dialogUtil(this);
  auto path = dialogUtil.chooseSavePath();

  // if a path is available
  if (!path.empty()) {
    // simply load the data
    util::SignalFileActor fileActor(path);

    auto invertedSignal = std::shared_ptr<uanc::amv::InvertedModel>(new uanc::amv::InvertedModel());
    invertedSignal->left_channel = _signal->left_channel;
    invertedSignal->right_channel = _signal->right_channel;
    fileActor.saveData(invertedSignal);
  }
}

}
}