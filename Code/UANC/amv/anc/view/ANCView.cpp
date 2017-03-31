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

#include <Code/UANC/gui/PlotWidget.h>
#include "ANCView.h"

namespace uanc {
namespace amv {
namespace anc {
namespace view {

/** \brief Gets the complete widget.
 *
 * This function is used to retrieve the widget from the view. It gets
 * used for integration the main application. It creates a Plotwidget inside
 * of a QWidget and passes this back. Uses the singleton pattern to ensure the
 * unique creation of the widget.
 *
 * @return The created widget.
 */
QWidget *ANCView::produceWidget(){
  if (this->_widget == nullptr) {
    this->_plotWidget = std::unique_ptr<uanc::gui::PlotWidget>(new uanc::gui::PlotWidget());
    this->_widget = _plotWidget.get();
  }

  // return the created pointer
  return this->_widget;
}

/** \brief This method applies the model data.
 *
 * This method simply takes the passed data and places it inside of the
 * view at the appropriate places.
 *
 * @param data The applied data.
 */
void ANCView::setData(std::shared_ptr<model::ANCModel> data) {
  this->_plotWidget->setSignal(data);
}
}
}
}
}