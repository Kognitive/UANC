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
  virtual QWidget *getWidget() = 0;
};

}
}

#endif //UANC_IALGORITHMVIEW_H
