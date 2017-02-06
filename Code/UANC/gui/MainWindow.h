/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef CODE_UANC_GUI_MAINWINDOW_H_
#define CODE_UANC_GUI_MAINWINDOW_H_

#include <string>

#include <QApplication>
#include<QMenuBar>
#include <QtWidgets/QMainWindow>
#include <memory>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

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

 public:

  /** \brief Obtain a reference to the main window.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the main window.
   * In addition it uses a shared pointer.
   *
   * @return The shared pointer containing the MainWindow
   */
  static std::shared_ptr<MainWindow> get();

 private:

  /** \brief Holds the main widget of the main window.
   *
   * This field holds the main widget of the main widget. In detail
   * that means it gets used as the central widget later.
   */
  std::unique_ptr<MainWidget> mainWidget;

  /** \brief Represents the load action.
   *
   * Represents the load action. In detail it is the file open action
   */
  std::unique_ptr<QAction> fileOpenAction;

  /** \brief Represents the save action.
   *
   * Represents the save action. In detail it is the file save action
   */
  std::unique_ptr<QAction> fileSaveAction;

  /** \brief Represents the file menu itself.
   *
   * Represents the file menu itself. */
  std::unique_ptr<QMenu> fileMenu;

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
  static std::shared_ptr<MainWindow> _instance;

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

  /** These simply are the actions taken when you click inside of the menu */
 private slots:

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


  /** \brief Saves a file to the hard drive.
   *
   * This method displays a file save dialog. Then it saves the right signal to
   * the hard drive.
   */
  void saveFile();
};

}
}
#endif //CODE_UANC_GUI_MAINWINDOW_H
