//
// Created by jannewulf on 12.12.16.
//

#include "PlotWidget.h"

namespace uanc {
namespace gui {

PlotWidget::PlotWidget(bool hasError) {
  _hasError = hasError;
  this->initialize();
}

void PlotWidget::initialize() {
  // create the signal plot and the control plot
  std::shared_ptr<PlotWidget> sharedThis = std::shared_ptr<PlotWidget>(this);
  _signalPlot = std::shared_ptr<SignalPlot>(new SignalPlot(sharedThis));
  _control = std::shared_ptr<Control>(new Control(sharedThis));
  _chkBoxShowError = std::shared_ptr<QCheckBox>(new QCheckBox("Zeige Fehler"));

  // update plot when state of checkbox changes
  connect(_chkBoxShowError.get(), SIGNAL(toggled(bool)), _signalPlot.get(), SLOT(hideError(bool)));

  // set size policy, such that control has minimum height
  _control->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  // create the layout
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(_signalPlot.get());
  layout->addWidget(_control.get());
  if (_hasError)
    layout->addWidget(_chkBoxShowError.get());
  setLayout(layout);
}

void PlotWidget::setSignal(std::shared_ptr<Aquila::SignalSource> signal, std::shared_ptr<Aquila::SignalSource> originalSignal) {
  // save pointer to signal in member
  _signal = signal;
  if (originalSignal != NULL)
    _errorSignal = std::shared_ptr<Aquila::SignalSource>(new Aquila::SignalSource(*signal.get() + *originalSignal.get()));

  // create QCPDataMap and set data in both graphs
  // creating two maps because QCustomPlot requires raw pointers and we want to prevent null pointers
  double maxSignalAmplitude = std::numeric_limits<double>::min();
  double minSignalAmplitude = std::numeric_limits<double>::max();
  size_t n = _signal->getSamplesCount();
  QCPDataMap *newDataMain = new QCPDataMap;
  QCPDataMap *newDataControl = new QCPDataMap;
  QCPDataMap *newError = new QCPDataMap;
  QCPData newDatapoint;

  for (size_t i = 0; i < n; ++i) {
    newDatapoint.key = i;
    newDatapoint.value = _signal->sample(i);

    newDataMain->insertMulti(newDatapoint.key, newDatapoint);
    newDataControl->insertMulti(newDatapoint.key, newDatapoint);

    // keep track of max and min amplitude
    maxSignalAmplitude = std::max(maxSignalAmplitude, newDatapoint.value);
    minSignalAmplitude = std::min(minSignalAmplitude, newDatapoint.value);

    if (originalSignal != NULL) {
      newDatapoint.value = _errorSignal->sample(i);
      newError->insertMulti(newDatapoint.key, newDatapoint);
    }
  }

  _signalPlot->setData(newDataMain, false);
  if (originalSignal != NULL)
    _signalPlot->setError(newError, false);
  _control->setData(newDataControl, maxSignalAmplitude, minSignalAmplitude, n, false);
}

const QCPRange PlotWidget::getPlotXRange() const {
  return _signalPlot->xAxis->range();
}

void PlotWidget::plotChanged() {
  _control->updateNavBox(getPlotXRange());
}

void PlotWidget::controlChanged() {
  double left = _control->getBoxLeft();
  double right = _control->getBoxRight();
  _signalPlot->setRange(left, right);
}

}
}