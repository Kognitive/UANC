/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef CODE_UANC_GUI_MAINWINDOW_H_
#define CODE_UANC_GUI_MAINWINDOW_H_

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <memory>

namespace uanc {
namespace gui {

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
  static std::shared_ptr<MainWindow> Get(int &, char **);

  /** \brief Show the main window on the screen.
   *
   * This method can be used to show the main window. It basically executes the show method
   * of the QMainWindow and executes the QTContext
   */
  void show();

 private:

  /** \brief Private constructor to deny creation outside of the singleton pattern.
   *
   * This constructor takes a QApplication and saves it internally as it context.
   *
   * \param context Represents the context in which the window get shown.
   */
  MainWindow(QApplication *context);

  /** \brief Shared pointer of the one and only instance of MainWindow.
   *
   * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
   * there are no dangling pointer referring to MainWindow.
   */
  static std::shared_ptr<MainWindow> _instance;

  /** \brief This is the context of the application.
   *
   * The MainWindow itself is unique. Therefore we can apply a unique pointer
   * at this place.
   */
  std::unique_ptr<QApplication> _context;
};

}
}
#endif //CODE_UANC_GUI_MAINWINDOW_H
