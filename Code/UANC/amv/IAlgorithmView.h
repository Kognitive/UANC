/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_IALGORITHMVIEW_H
#define UANC_IALGORITHMVIEW_H

#include <QtWidgets/QWidget>

namespace uanc {
namespace amv {

/** \brief The general interface for every view.
 *
 * This interface has to implemented by any view, which should be used
 * seamlesly in the main application.
 */
class IAlgorithmView {

 public:

  /** \brief Gets the complete widget.
   *
   * This function is used to retrieve the widget from the view. It gets
   * used for integration the main application
   *
   * @return The created widget.
   */
  QWidget *getWidget() {
    if (this->_widget == nullptr) {
      this->_widget = this->produceWidget();
    }

    // return the created pointer
    return this->_widget;
  }

  /** \brief Produces the widget.
   *
   * This function is used to produce the widget from the view. It gets
   * used for integration the main application
   *
   * @return The created widget.
   */
  virtual QWidget *produceWidget() = 0;

 private:

  /** \brief This represents a weak pointer to the constructed QWidget.
   *
   * This holds a reference to the associated QWidget, if there was one created.
   */
  QWidget *_widget = nullptr;
};

}
}

#endif //UANC_IALGORITHMVIEW_H
