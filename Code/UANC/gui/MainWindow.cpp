/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "MainWindow.h"
#include "Code/UANC/util/SignalFileActor.h"

namespace uanc {
namespace gui {

/** \brief Obtain a reference to the main window.
 *
 * Uses a classical singleton pattern to give back exactly the same copy of the main window.
 * In addition it uses a shared pointer.
 *
 * @return The shared pointer containing the MainWindow
 */
std::shared_ptr<MainWindow> MainWindow::get() {
  if (!_instance) {
    _instance = std::shared_ptr<MainWindow>(new MainWindow());
  }

  return _instance;
}

/** \brief Private constructor to deny creation outside of the singleton pattern.
 *
 * This constructor takes a QApplication and saves it internally as it context.
 *
 * \param context Represents the context in which the window get shown.
 */
MainWindow::MainWindow() {
  //Get an instance of the import window.
  importWindow = ImportWindow::get();
  //Connect its signals to the corresponding functions
  connect(&*importWindow, &ImportWindow::indicesLoaded, this, &MainWindow::showImportedSignals);

  this->setupGUI();
}

/** \brief This method will setup the gui appropriately
 *
 * It creates basically a main widget and a menu inside of the main window.
 */
void MainWindow::setupGUI() {
  auto widget = new MainWidget();
  setCentralWidget(widget);
  this->mainWidget = widget;

  // basically create the top menu
  this->makeActions();
  this->makeMenu();

  // change the window title to a longer one.
  this->setWindowTitle("Understanding Active Noise Cancelling");
}

/** \brief This method creates the appropriate actions and links them accordingely
 *
 * Simply link the actions and create them.
 */
void MainWindow::makeActions() {

  // create the file open action
  fileOpenAction = std::unique_ptr<QAction>(new QAction(tr("&Import File..."), this));
  fileOpenAction->setShortcuts(QKeySequence::Open);
  fileOpenAction->setStatusTip(tr("Import a file"));
  connect(fileOpenAction.get(), &QAction::triggered, this, &MainWindow::loadFile);
  this->addAction(fileOpenAction.get());

  // create the application close action
  ApplicationCloseAction = std::unique_ptr<QAction>(new QAction(tr("&Quit"), this));
  ApplicationCloseAction->setShortcuts(QKeySequence::Quit);
  ApplicationCloseAction->setStatusTip(tr("Quit"));
  connect(ApplicationCloseAction.get(), &QAction::triggered, this, &MainWindow::close);
  this->addAction(ApplicationCloseAction.get());

}


/** \brief This method creates the top menu
 *
 * This method sets up the top menu inside of the application.
 */
void MainWindow::makeMenu() {

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(fileOpenAction.get());
  fileMenu->addAction(ApplicationCloseAction.get());
}

/** \brief Loads a file from plate and displays it inside of the gui.
 *
 * This method should open a dialog, to let the user select a file. Then
 * it loads that specified file and in the end it gets drawn to the MainWidget
 * left plot.
 */
void MainWindow::loadFile() {

  //Open the import dialog
  importWindow->show();
  importWindow->raise();
  importWindow->activateWindow();

}

void MainWindow::showImportedSignals(std::vector<int> loadedIndices) {

  for (int signalID : loadedIndices)
  {
    this->mainWidget->loadSignalSource(SignalManager::get()->getSignal(signalID));
  }
}

void MainWindow::closeEvent(QCloseEvent *) {
  importWindow->close();
}

/** \brief Shared pointer of the one and only instance of MainWindow.
 *
 * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
 * there are no dangling pointer referring to MainWindow.
 */
std::shared_ptr<MainWindow> MainWindow::_instance = NULL;

}
}


