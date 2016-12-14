//
// Created by markus on 12/13/16.
//

#ifndef UANC_FFTVIEW_H
#define UANC_FFTVIEW_H

#include "AlgorithmView.h"

namespace uanc { namespace gui { namespace views {

/** \brief Represents an algorithm view, which can be used inside
 * of the application.
 *
 * This represents a algorithm view which can be used with an appropriate model.
 */
class FFTView : public AlgorithmView {

 public:

  /** \brief Should be publically constructable.
   *
   * Simple constructor for creating such an object.
   */
  FFTView();

  /** \brief Function to build the unique Widget.
   *
   * This has to be overriden in order to build the unique widget. When the standard
   * implementation is used, there will be no element added.
   *
   * @return The unique widget, created as a qwidget.
   */
  QWidget* buildUniqueWidget() {
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
  void setUniqueData(model::AlgorithmModel* data) {
    //TODO fft plots
  }
};

}}}

#endif //UANC_FFTVIEW_H
