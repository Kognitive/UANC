/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "MainWidget.h"

namespace uanc {
namespace gui {

/** \brief This is the main widget constructor.
 *
 * This basically initializes the gui and does some other
 * initialization stuff.
 */
MainWidget::MainWidget() {
  this->setupGUI();
}

/** \brief This method will setup the gui appropriately
 *
 * It creates basically a main widget and a menu inside of the main window.
 */
void MainWidget::setupGUI() {

  // create the layout and right and left button
  QVBoxLayout *layout = new QVBoxLayout;
  auto button = new QPushButton("Direct Inverse");
  this->_buttonLeft = std::unique_ptr<QPushButton>(new QPushButton("Direct Inverse"));
  this->_buttonRight = std::unique_ptr<QPushButton>(new QPushButton("FFT Inverse"));

  // map to the signal slots in the application
  connect(button, SIGNAL (clicked()),this, SLOT (this->directInverseClicked()));
  connect(this->_buttonRight.get(), SIGNAL (clicked()),this, SLOT (this->fftInverseClicked()));

  // create the bottom and top plot
  this->_plotTop = std::unique_ptr<QCustomPlot>(new QCustomPlot());
  this->_plotBottom = std::unique_ptr<QCustomPlot>(new QCustomPlot());
  this->_plotTop->addGraph();
  this->_plotBottom->addGraph();

  // basically create a hbox layout
  QWidget *hbar = new QWidget;
  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->addWidget(button);
  hlayout->addWidget(this->_buttonRight.get());
  hbar->setLayout(hlayout);

  // construct the complete layout
  layout->addWidget(_plotTop.get());
  layout->addWidget(hbar);
  layout->addWidget(_plotBottom.get());

  this->setLayout(layout);
  this->show();
}

/** \brief Basically places an input signal inside of the widget.
 *
 * This sets an input signal inside of the widget
 * @param signalSource the signal source to set
 */
void MainWidget::setSignalInputSource(std::shared_ptr<Aquila::SignalSource> signalSource) {
  _signalInputSource = signalSource;
  this->plotSignal(_signalInputSource, PlotPosition::TOP);
}

/** \brief Gets the output signal of the widget.
 *
 * This method gets the output signal of the method.
 * @return The signal source of the output
 */
std::shared_ptr<Aquila::SignalSource> MainWidget::getSignalOutputSource() {
  return _signalOutputSource;
}

/** \brief This method should simply plot the signal to the top or bottom plot
 *
 * This should plot the signal to the top and bottom plot. Please be aware of resizing the plot, so that
 * the signal is good visible. Note that in a later iteration we will add a functionality to scroll the singal,
 * so don't change the method signature, because the subwidget itself has to do the correct resizing.
 *
 * @param signal The signal which should be used during this
 * @param position The position of the plot. e.g. Top or bottom.
 */
void MainWidget::plotSignal(std::shared_ptr<Aquila::SignalSource> signal, PlotPosition position) {
  //TODO Graph plotten
}

/** \brief This gets fired, when the direct inverse button is clicked
 *
 * Gets fired, whenever a user clicks on the direct inverse button.
 */
void MainWidget::directInverseClicked() {
  auto directInverseAlgorithm = new algorithm::InverseDirectAlgorithm();
  auto generalAlgorithm = dynamic_cast<algorithm::Algorithm*>(directInverseAlgorithm);
  this->applyAlgorithm(generalAlgorithm);
  delete directInverseAlgorithm;
}

/** \brief This gets fired, when the inverse fft button is clicked
 *
 * This method is fired, whenever a user clicks on the fftinverse button inside of the gui
 */
void MainWidget::fftInverseClicked() {
  auto fftInverseAlgorithm = new algorithm::InverseFFTAlgorithm();
  auto generalAlgorithm = dynamic_cast<algorithm::Algorithm*>(fftInverseAlgorithm);
  this->applyAlgorithm(generalAlgorithm);
  delete fftInverseAlgorithm;
}

/** \brief This method can be used to apply an algorithm to the inner data.
 *
 * This algorithm basically applies the algorithm to the inner data.
 *
 * @param algorithm The algorithm to use
 */
void MainWidget::applyAlgorithm(algorithm::Algorithm *algorithm) {

  // basically create the input vector
  std::vector<std::shared_ptr<Aquila::SignalSource>> input(1);
  input.push_back(this->_signalInputSource);

  // apply the algorithm
  auto output = algorithm->execute(input);

  // afterwards save the result internally and plot the graph as well
  this->_signalOutputSource = output.at(0);
  this->plotSignal(_signalOutputSource, PlotPosition::BOTTOM);
}

}}