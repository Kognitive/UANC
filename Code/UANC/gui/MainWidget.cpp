/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <Code/UANC/util/tools/Path.h>
#include <Code/libs/aquila/source/WaveFile.h>
#include <Code/UANC/amv/anc/algorithm/InverseFFTAlgorithm.h>
#include <Code/UANC/amv/anc/ANCAlgorithmRegister.h>
#include <iostream>
#include "MainWidget.h"
#include "SignalViewWidget.h"

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

  // register algorithms and add them to the combobox
  this->_algorithmList = uanc::amv::anc::ANCAlgorithmRegister::getAlgorithms();
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
  this->_tabWidget = std::unique_ptr<QTabWidget>(new QTabWidget());
  this->_tabWidget.get()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  this->_tabWidget->setTabsClosable(true);
  connect(this->_tabWidget.get(), SIGNAL(tabCloseRequested(int)), this, SLOT(waveClosed(int)));

  // construct the complete layout
  this->_detailTabWidget = std::unique_ptr<QTabWidget>(new QTabWidget());
  this->_detailTabWidget.get()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  this->_detailTabWidget->setTabsClosable(true);
  connect(this->_detailTabWidget.get(),
          SIGNAL(tabCloseRequested(int)),
          this,
          SLOT(algorithmClosed(int)));

  // add new algorithm for a chosen detailTabWidget
  connect(this->_tabWidget.get(), SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));

  layout->addWidget(this->_tabWidget.get());
  layout->addWidget(hbar);
  layout->addWidget(this->_detailTabWidget.get());

  this->setLayout(layout);
  this->show();
}

/** \brief This method gets used to show the algorithms inside of the combobox
 *
 * This method displays the algorithms inside of the combobox.
 */
void MainWidget::showAvailableAlgorithms() {

  // get size of algorithm list
  auto size = this->_algorithmList->size();

  // now basically iterate over the elements
  for (auto i = -1; ++i < size;) {
    this->_cmbAlgorithm->addItem(QString::fromStdString(this->_algorithmList->at(i)->getName()));
  }
}

/** \brief This gets fired, when the direct inverse button is clicked
 *
 * Gets fired, whenever a user clicks on the direct inverse button.
 */
void MainWidget::applyClicked() {

  // get the current index and using that get the correct algorithm
  // After that simply apply the algorithm
  auto currentIndex = _cmbAlgorithm->currentIndex();
  auto algorithm = this->_algorithmList->at(currentIndex)->clone();

  this->applyAlgorithm(*algorithm);
  auto index = this->_tabWidget->currentIndex();

  // get the mapping list and push back the algorithm save afterwards
  auto vec = this->_waveAlgorithMapping.at(index);
  vec->push_back(std::shared_ptr<uanc::amv::IAlgorithm>(algorithm));
  this->_waveAlgorithMapping.insert(std::make_pair(index, vec));

  // we want to simply derive a anc a view and combine them
  this->_detailTabWidget->addTab(algorithm->getView()->getWidget(),
                                 QString::fromStdString(algorithm->getName()));
  algorithm->fillView();
}

bool tabInRun = false;

/** \brief Simple signal for a differenct selected tab */
void MainWidget::tabSelected() {

  if (tabInRun) return;

  // remove all tabs from the detail widget
  for (int i = this->_detailTabWidget->count() - 1; i >= 0; --i) {
    this->_detailTabWidget->removeTab(i);
  }

  // get the list of algorithms
  auto index = this->_tabWidget->currentIndex();

  // get the mapping list and push back the algorithm save afterwards
  auto vec = this->_waveAlgorithMapping.at(index);

  // iterate over vector and fill new plots in
  for (auto it = vec->begin(); it != vec->end(); ++it) {

    auto algo = (*it).get();
    this->_detailTabWidget->addTab(algo->getView()->getWidget(),
                                   QString::fromStdString(algo->getName()));
    this->_detailTabWidget->update();
  }
}

/** \brief loads the signal source.
 *
 * This method loads a signal source in the top tab view.
 * @param signalSource the signal source to load.
 */
void MainWidget::loadSignalSource(std::shared_ptr<InvertedModel> signalSource) {

  auto widget = new SignalViewWidget();
  widget->setSignalModel(signalSource);

  // Simply add the tab and block the rest
  tabInRun = true;
  std::string text = "Standard";
  auto castedObj = std::dynamic_pointer_cast<Aquila::WaveFile>(signalSource->left_channel);
  if (castedObj.get() != nullptr) {
    text = uanc::util::Path::getFileName(castedObj->getFilename());
  }

  auto index = this->_tabWidget->addTab(widget, QString::fromStdString(text));
  tabInRun = false;

  auto vec = std::make_shared<std::vector<std::shared_ptr<uanc::amv::IAlgorithm>>>();
  this->_waveAlgorithMapping.insert(std::make_pair(index, vec));
}

/** \brief This method can be used to apply an algorithm to the inner data.
 *
 * This algorithm basically applies the algorithm to the inner data.
 *
 * @param algorithm The algorithm to use
 */
void MainWidget::applyAlgorithm(uanc::amv::IAlgorithm &algorithm) {

  // check if signal available if not present a messagebox and
  // ask the user to load a signal.
  auto signalManager = SignalManager::get();
  auto index = this->_tabWidget->currentIndex();
  auto signal = signalManager->getSignal(index);
  if (signal == NULL) {
    QMessageBox msgBox;
    msgBox.setText("You have to load a signal first. Pleasy use File -> Open File...");
    msgBox.setWindowTitle("No signal loaded.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    return;
  }

  // apply the algorithm
  algorithm.process(signal);
}

void MainWidget::waveClosed(const int &index) {
  if (index == -1) {
    return;
  }

  // get tabitem widget
  QWidget *tabItem = this->_tabWidget->widget(index);

  tabInRun = true;
  // Removes the tab at position index from this stack of widgets.
  // The page widget itself is not deleted.
  this->_tabWidget->removeTab(index);
  tabInRun = false;

  // additionally remove the algorithm from the inner mapping
  auto vec = std::make_shared<std::vector<std::shared_ptr<uanc::amv::IAlgorithm>>>();

  // iterate from closed to end
  for (int i = index; i < this->_tabWidget->count(); ++i) {
    auto vec = this->_waveAlgorithMapping.at(i + 1);
    this->_waveAlgorithMapping.erase(i);
    this->_waveAlgorithMapping.insert(std::make_pair(i, vec));
  }

  // Deleate signal
  auto signalManager = SignalManager::get();
  signalManager->eraseSignal(index);

  // do the final erase
  this->_waveAlgorithMapping.erase(this->_tabWidget->count());

  // special case occurs, when it was the last tab
  if (this->_tabWidget->count() > 0) {
    this->tabSelected();
  } else {
    // remove all tabs from the detail widget
    for (int i = this->_detailTabWidget->count() - 1; i >= 0; --i) {
      this->_detailTabWidget->removeTab(i);
    }
  }
}

void MainWidget::algorithmClosed(const int &index) {
  if (index == -1) {
    return;
  }

  // get tabitem widget
  QWidget *tabItem = this->_detailTabWidget->widget(index);

  tabInRun = true;
  // Removes the tab at position index from this stack of widgets.
  // The page widget itself is not deleted.
  this->_detailTabWidget->removeTab(index);
  tabInRun = false;

  // additionally remove the algorithm from the inner mapping
  auto vec = std::make_shared<std::vector<std::shared_ptr<uanc::amv::IAlgorithm>>>();

  // get the top index
  auto indexTop = this->_tabWidget->currentIndex();

  auto el = this->_waveAlgorithMapping.at(indexTop);
  el->erase(el->begin() + index);
}

}
}