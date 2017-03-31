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

#ifndef CODE_UANC_GUI_MAINWINDOW_H_
#define CODE_UANC_GUI_MAINWINDOW_H_

#include <QApplication>
#include<QMenuBar>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <string>
#include <memory>
#include <vector>

#include "MainWidget.h"
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/UANC/util/SignalManager.h"
#include "ImportWindow.h"

namespace uanc {
namespace gui {

class ImportWindow;

/** \brief This class represents the main window.
 *
 * It is a QMainWindow. So you can think of it as a wrapper to extend the
 * functionality of a basic QMainWindow
 */
class MainWindow : public QMainWindow {
 protected:
  /** \brief This method executes all necessary actions when the main application is closed
   *
   * It executes all necessary actions when the main application is closed
   */
  void closeEvent(QCloseEvent *);

 public:
  /** \brief Hol a reference to the main window.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the main window.
   * In addition it uses a shared pointer.
   *
   * @return The shared pointer containing the MainWindow
   */
  static MainWindow* get();

 private:
  /** \brief Holds the main widget of the main window.
   *
   * This field holds the main widget of the main widget. In detail
   * that means it gets used as the central widget later.
   */
  MainWidget *mainWidget;

  /** \brief Represents the load action.
   *
   * Represents the load action. In detail it is the file open action
   */
  std::unique_ptr<QAction> fileOpenAction;
  std::unique_ptr<QAction> aboutAction;

  /** \brief Represents the close action.
 *
 * Represents the close action. In detail it is the application close action
 */
  std::unique_ptr<QAction> ApplicationCloseAction;
  /** \brief Represents the file menu itself.
   *
   * Represents the file menu itself. */
  QMenu *fileMenu;

  /** \brief Private constructor to deny creation outside of the singleton pattern.
   *
   * This constructor takes a QApplication and saves it internally as it context.
   */
  MainWindow();

  /** \brief Shared pointer of the one and only instance of MainWindow.
   *
   * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
   * there are no dangling pointer referring to MainWindow.
   */
  static MainWindow* _instance;

  /** \brief This method will setup the gui appropriately
   *
   * It creates basically a main widget and a menu inside of the main window.
   */
  void setupGUI();

  /** \brief This method creates the appropriate actions and links them accordingely
   *
   * Simply link the actions and create them.
   */
  void makeActions();

  /** \brief This method creates the top menu
   *
   * This method sets up the top menu inside of the application.
   */
  void makeMenu();

  void about(); public slots:

  /** \brief Loads a file from plate and displays it inside of the gui.
   *
   * This method should open the import dialog, to let the user select a file. Then
   * it loads that specified file and in the end it gets drawn to the MainWidget
   * left plot.
   */
  void loadFile();

  /** \brief Imports the signals selected using the Importer into the main window
   *  @param: The indices of the imported signals that have been selected.
   */
  void showImportedSignals(std::vector<int> loadedIndices);
};

}  // namespace gui
}  // namespace uanc

#endif  // CODE_UANC_GUI_MAINWINDOW_H_
