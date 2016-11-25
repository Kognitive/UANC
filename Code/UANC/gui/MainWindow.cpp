/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "MainWindow.h"

namespace uanc {
namespace gui {

/** \brief Obtain a reference to the main window.
 *
 * Uses a classical singleton pattern to give back exactly the same copy of the main window.
 * In addition it uses a shared pointer.
 *
 * @return The shared pointer containing the MainWindow
 */
std::shared_ptr<MainWindow> MainWindow::Get(int &argc, char **argv) {
  if (!_instance) {
    auto context = new QApplication(argc, argv);
    _instance = std::shared_ptr<MainWindow>(new MainWindow(context));
  }

  return _instance;
}

/** \brief Show the main window on the screen.
 *
 * This method can be used to show the main window. It basically executes the show method
 * of the QMainWindow and executes the QTContext
 */
void MainWindow::show() {
  QMainWindow::show();
  _context->exec();
}

/** \brief Private constructor to deny creation outside of the singleton pattern.
 *
 * This constructor takes a QApplication and saves it internally as it context.
 *
 * \param context Represents the context in which the window get shown.
 */
MainWindow::MainWindow(QApplication *context) : _context(context) {
}

/** \brief Shared pointer of the one and only instance of MainWindow.
 *
 * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
 * there are no dangling pointer referring to MainWindow.
 */
std::shared_ptr<MainWindow> MainWindow::_instance = NULL;

}
}
