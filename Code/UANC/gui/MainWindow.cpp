/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Code/UANC/gui/MainWindow.h"

namespace uanc {
namespace gui {

/** \brief Obtain a reference to the main window.
 *
 * Uses a classical singleton pattern to give back exactly the same copy of the main window.
 * In addition it uses a shared pointer.
 *
 * @return The shared pointer containing the MainWindow
 */
MainWindow *MainWindow::get() {
  if (!_instance) {
    _instance = new MainWindow();
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
  // Get an instance of the import window.
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
  this->setWindowTitle("Antischall");
}

/** \brief This method creates the appropriate actions and links them accordingely
 *
 * Simply link the actions and create them.
 */
void MainWindow::makeActions() {
  // create the file open action
  fileOpenAction = std::unique_ptr<QAction>(
      new QAction(tr("&Import File..."), this));
  fileOpenAction->setShortcuts(QKeySequence::Open);
  fileOpenAction->setStatusTip(tr("Import a file"));
  connect(fileOpenAction.get(),
          &QAction::triggered,
          this, &MainWindow::loadFile);
  this->addAction(fileOpenAction.get());

  // create the about action
  aboutAction = std::unique_ptr<QAction>(new QAction(tr("&About"), this));
  aboutAction->setStatusTip(tr("About"));
  connect(aboutAction.get(), &QAction::triggered, this, &MainWindow::about);
  this->addAction(aboutAction.get());

  // create the application close action
  ApplicationCloseAction = std::unique_ptr<QAction>(
      new QAction(tr("&Quit"), this));
  ApplicationCloseAction->setShortcuts(QKeySequence::Quit);
  ApplicationCloseAction->setStatusTip(tr("Quit"));
  connect(ApplicationCloseAction.get(),
          &QAction::triggered, this, &MainWindow::close);
  this->addAction(ApplicationCloseAction.get());
}

/** \brief This method creates the top menu
 *
 * This method sets up the top menu inside of the application.
 */
void MainWindow::makeMenu() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(fileOpenAction.get());
  fileMenu->addAction(aboutAction.get());
  fileMenu->addAction(ApplicationCloseAction.get());
}

/** \brief Loads a file from plate and displays it inside of the gui.
 *
 * This method should open a dialog, to let the user select a file. Then
 * it loads that specified file and in the end it gets drawn to the MainWidget
 * left plot.
 */
void MainWindow::loadFile() {
  auto importWindow = new ImportWindow(this);

  // Connect its signals to the corresponding functions
  connect(&*importWindow,
          &ImportWindow::indicesLoaded,
          this, &MainWindow::showImportedSignals);

  // Open the import dialog
  importWindow->show();
  importWindow->raise();
  importWindow->activateWindow();
}

void MainWindow::showImportedSignals(std::vector<int> loadedIndices) {
  for (int signalID : loadedIndices) {
    this->mainWidget->loadSignalSource(
        uanc::util::SignalManager::get()->getSignal(signalID));
  }
}

void MainWindow::closeEvent(QCloseEvent *) {
}
/** \brief Loads a file from plate and displays it inside of the gui.
 *
 * This method should open a dialog, to let the user select a file. Then
 * it loads that specified file and in the end it gets drawn to the MainWidget
 * left plot.
 */
void MainWindow::about() {
  QMessageBox::about(this, "About", "Antischall Ver. 1.1.7 \n "
      "Developers: \n"
      "\t Daniel José Ceballos Jung \n"
      "\t Janne Wulf \n"
      "\t Markus Semmler \n"
      "\t Roman Rempel \n"
      "\t Vladimir Roskin");
}

/** \brief Shared pointer of the one and only instance of MainWindow.
 *
 * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
 * there are no dangling pointer referring to MainWindow.
 */
MainWindow *MainWindow::_instance = nullptr;

}  // namespace gui
}  // namespace uanc
