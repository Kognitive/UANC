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

#include "Code/UANC/amv/anc/view/PMView.h"
#include "Code/UANC/util/GlobalSettings.h"

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
QWidget *PMView::produceWidget() {
  // create the widgets for the view
  this->_signalViewWidget =
      std::unique_ptr<uanc::gui::SignalViewWidget>(
          new uanc::gui::SignalViewWidget(
              uanc::util::GlobalSettings::get()->currentIndex));
  this->_treeview = std::unique_ptr<uanc::gui::PMWidget>(
      new uanc::gui::PMWidget());

  // set horizontal layout (splitter)
  this->_layout =  new QHBoxLayout;
  this->_layout->addWidget(_signalViewWidget.get());
  this->_layout->addWidget(_treeview.get());
  _treeview->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
  auto widget = new QWidget();
  widget->setLayout(_layout);

  // return the created pointer
  return widget;
}

/** \brief This method applies the model data.
 *
 * This method simply takes the passed data and places it inside of the
 * view at the appropriate places.
 *
 * @param data The applied data.
 */
void PMView::setData(std::shared_ptr<model::ANCModel> signalData) {
  this->_signalViewWidget->setSignalModel(signalData);
  this->_treeview->setData(signalData->defaultRegister.getCustomMeasurements());
}

}  // namespace view
}  // namespace anc
}  // namespace amv
}  // namespace uanc
