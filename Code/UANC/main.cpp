#include <iostream>
#include <Code/UANC/gui/MainWindow.h>
#include <Code/UANC/util/GlobalSettings.h>

using namespace uanc::gui;

// globally define settings
GlobalSettings* GlobalSettings::globalSettings = nullptr;

int main(int argc, char **argv) {

  // Create the application context
  QApplication a(argc, argv);

  // Create a new QTGuiContext. Afterwards basically execute the desired subwindow
  auto mainwindow = MainWindow::get();

  mainwindow->resize(1000, 800);
  mainwindow->show();

  auto code = a.exec();

  return code;
}