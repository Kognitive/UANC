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

  // create the layout. Therefore create the apply button
  // and the corresponding combobox displaying the algorithms
  QVBoxLayout *layout = new QVBoxLayout;
  this->_buttonApply = std::unique_ptr<QPushButton>(new QPushButton("Apply"));
  this->_cmbAlgorithm = std::unique_ptr<QComboBox>(new QComboBox());

  // connect the handler to the button
  connect(this->_buttonApply.get(), SIGNAL (clicked()), this, SLOT (applyClicked()));

  // create the bottom and top plot
  this->_plotTop = std::unique_ptr<QCustomPlot>(new QCustomPlot());
  this->_plotBottom = std::unique_ptr<QCustomPlot>(new QCustomPlot());
  this->_plotTop->addGraph();
  this->_plotBottom->addGraph();

  // register algorithms and add them to the combobox
  this->registerAlgorithms();
  this->showAvailableAlgorithms();

  // basically create a hbox layout
  QWidget *hbar = new QWidget;
  QHBoxLayout *hlayout = new QHBoxLayout;

  // add subwidgets and set the correct size policies
  this->_buttonApply.get()->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
  hlayout->addWidget(this->_cmbAlgorithm.get());
  hlayout->addWidget(this->_buttonApply.get());

  // set the correct layout options
  hbar->setLayout(hlayout);
  hbar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  // construct the complete layout
  layout->addWidget(_plotTop.get());
  layout->addWidget(hbar);
  layout->addWidget(_plotBottom.get());

  this->setLayout(layout);
  this->show();
}

/** \brief This method can be used to register the algorithms inside of the gui
 *
 * This method gets used to register the available algorithms.
 */
void MainWidget::registerAlgorithms() {
  using namespace uanc::algorithm;

  this->_algorithmList = std::vector<Algorithm*>();

  // Here you can add further algorithms. If register them here, they
  // will be included further inside the ecosystem automatically.

  // add first algorithms
  auto invDirect = new InverseDirectAlgorithm();
  this->_algorithmList.push_back(invDirect);

  // add second algorithms
  auto invFFT = new InverseFFTAlgorithm();
  this->_algorithmList.push_back(invFFT);
}

/** \brief This method gets used to show the algorithms inside of the combobox
 *
 * This method displays the algorithms inside of the combobox.
 */
void MainWidget::showAvailableAlgorithms() {
  using namespace uanc::algorithm;

  // get size of algorithm list
  auto size = this->_algorithmList.size();

  // now basically iterate over the elements
  for (auto i = -1; ++i < size; ) {
    this->_cmbAlgorithm->addItem(QString::fromStdString(this->_algorithmList[i]->getName()));
  }
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
void MainWidget::applyClicked(){

  // get the current index and using that get the correct algorithm
  // After that simply apply the algorithm
  auto currentIndex = _cmbAlgorithm->currentIndex();
  auto algorithm = this->_algorithmList[currentIndex];
  this->applyAlgorithm(*algorithm);
}

/** \brief This method can be used to apply an algorithm to the inner data.
 *
 * This algorithm basically applies the algorithm to the inner data.
 *
 * @param algorithm The algorithm to use
 */
void MainWidget::applyAlgorithm(algorithm::Algorithm &algorithm) {

  // basically create the input vector
  std::vector<std::shared_ptr<Aquila::SignalSource>> input(1);

  // check if signal available if not present a messagebox and
  // ask the user to load a signal.
  if (this->_signalInputSource == NULL) {
    QMessageBox msgBox;
    msgBox.setText("You have to load a signal first. Pleasy use File -> Open File...");
    msgBox.setWindowTitle("No signal loaded.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    return;
  }

  input.push_back(this->_signalInputSource);

  // apply the algorithm
  auto output = algorithm.execute(input);

  // afterwards save the result internally and plot the graph as well
  this->_signalOutputSource = output.at(0);
  this->plotSignal(_signalOutputSource, PlotPosition::BOTTOM);
}

}}