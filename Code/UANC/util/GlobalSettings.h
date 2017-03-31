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

#ifndef UANC_GLOBALSETTINGS_H
#define UANC_GLOBALSETTINGS_H

#include <iostream>

namespace uanc {
    namespace util {
        using namespace std;

        class GlobalSettings {
        public:
            // sets the current index to zero
            int currentIndex = 0;

            static GlobalSettings *globalSettings;

            /** \brief The default Constructor
         *
         */
            static GlobalSettings *get() {
                if (globalSettings == nullptr) {
                    globalSettings = new GlobalSettings();
                }
                return globalSettings;
            };
        };
    }
}

#endif //UANC_GLOBALSETTINGS_H
