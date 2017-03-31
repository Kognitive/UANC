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

#include <Code/UANC/gui/MainWindow.h>
#include <Code/UANC/util/GlobalSettings.h>
#include <Code/UANC/util/tests/EpsilonTests.h>


using namespace uanc::gui;
using namespace uanc::util::event;

// globally define settings
uanc::util::GlobalSettings* uanc::util::GlobalSettings::globalSettings = nullptr;

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

  auto code = a.exec();

    EventManager::destroy();

  return code;
}