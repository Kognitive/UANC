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

#ifndef CODE_UANC_AMV_IALGORITHMVIEW_H_
#define CODE_UANC_AMV_IALGORITHMVIEW_H_

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

}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_IALGORITHMVIEW_H_
