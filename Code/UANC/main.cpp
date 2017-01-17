#include <iostream>
#include <Code/UANC/gui/MainWindow.h>

using namespace uanc::gui;

int main(int argc, char **argv) {

  // Create the application context
  QApplication a(argc, argv);

  // Create a new QTGuiContext. Afterwards basically execute the desired subwindow
  auto mainwindow = MainWindow::get();

  mainwindow->resize(1000, 800);
  mainwindow->show();

  return a.exec();
}