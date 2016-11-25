#include <iostream>
#include <Code/UANC/gui/MainWindow.h>

using namespace uanc::gui;

int main(int argc, char **argv) {

    // Create a new QTGuiContext. Afterwards basically execute the desired subwindow
    auto mainwindow = MainWindow::Get(argc, argv);

    mainwindow->resize(1000, 800);
    mainwindow->show();

    return 0;
}