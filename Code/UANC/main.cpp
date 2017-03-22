
#include <Code/UANC/gui/MainWindow.h>
#include <Code/UANC/util/Tests/EpsilonTests.h>


using namespace uanc::gui;

int main(int argc, char **argv) {

        for (int i = 0; i < argc; i++) {
            std::string argument = argv[i];
            if ((argument.compare("-t") == 0) && (argv[i+1] != NULL)) {
                //Start EpsilonTest
                EpsilonTests epsilonTests = EpsilonTests();
                std::string path = argv[i+1];
                epsilonTests.run(path);
                return 0;
            }
        }

        // Create the application context
        QApplication a(argc, argv);

        // Create a new QTGuiContext. Afterwards basically execute the desired subwindow
        auto mainwindow = MainWindow::get();

        mainwindow->resize(1000, 800);
        mainwindow->show();

        return a.exec();

}