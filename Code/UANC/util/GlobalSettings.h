//
// Created by markus on 22.03.17.
//

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
