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

#ifndef CODE_UANC_AMV_ANC_VIEW_PMVIEW_H_
#define CODE_UANC_AMV_ANC_VIEW_PMVIEW_H_

#include <QtWidgets/QWidget>
#include <memory>
#include "Code/UANC/amv/InvertedModel.h"
#include "Code/UANC/amv/AlgorithmView.h"
#include "Code/UANC/util/tools/Path.h"
#include "Code/UANC/gui/PMWidget.h"
#include "Code/UANC/amv/anc/model/ANCModel.h"
#include "Code/UANC/gui/SignalViewWidget.h"

namespace uanc {
namespace amv {
namespace anc {
namespace view {

/** \brief Represents an PMView.
 *
 * This represents a general PMView. It operates on an ANCModel and PMModel. It displays a simple
 * plot of the the inverted signal and performance informations of the algorithm.
 * It is a specialization of the more general AlgorithmView.
 */
class PMView : public uanc::amv::AlgorithmView<model::ANCModel> {
 public:
  /** \brief Gets the complete widget.
   *
   * This function is used to retrieve the widget from the view. It gets
   * used for integration the main application. It holds a Plotwidget and a TreeView inside
   * of a QWidget (horizontal layout) and passes this back.
   *
   * @return The created widget.
   */
  QWidget *produceWidget() final;

  /** \brief This method applies the model data.
  *
  * This method simply takes the passed data and places it inside of the
  * view at the appropriate places.
  *
  * @param data The applied data.
  */
  void setData(std::shared_ptr<model::ANCModel> signalData) final;

 private:
  /** \brief Holds a reference to the plot widget used inside.
   *
   * This field holds a unique reference to the internally used signal view widget.
   */
  std::unique_ptr<uanc::gui::SignalViewWidget> _signalViewWidget;

  /** \brief Holds a reference to the tree view used inside.
   *
   * This field holds a unique reference to the internally used tree view.
   */
  std::unique_ptr<uanc::gui::PMWidget> _treeview;

  /** \brief This represents a weak pointer to the constructed QSplitter.
   *
   * This holds a reference to the associated QSplitter, if there was one created.
   */
  QHBoxLayout *_layout = nullptr;
};

}  // namespace view
}  // namespace anc
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ANC_VIEW_PMVIEW_H_
