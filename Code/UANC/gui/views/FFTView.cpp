//
// Created by markus on 12/13/16.
//

#include "FFTView.h"

namespace uanc {
    namespace gui {
        namespace views {

            /** \brief Should be publically constructable.
             *
             * Simple constructor for creating such an object.
             */
            FFTView::FFTView() {

            }

            /** \brief Function to build the unique Widget.
             *
             * This has to be overriden in order to build the unique widget. When the standard
             * implementation is used, there will be no element added.
             *
             * @return The unique widget, created as a qwidget.
             */
            QWidget *FFTView::buildUniqueWidget() {
                //TODO fft plots
                return new QWidget();
            }

            /** \brief This represents the unique data.
             *
             * This has to be overriden in order to display the data in one
             * specififc way.
             *
             * @param data The data to apply to this view.
             */
            void FFTView::setUniqueData(model::AlgorithmModel *data) {
                //TODO fft plots
            }

        }
    }
}
