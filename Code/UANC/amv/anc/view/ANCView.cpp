/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
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
    this->_plotWidget = std::unique_ptr<uanc::gui::PlotWidget>(new uanc::gui::PlotWidget(true));
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
void ANCView::setData(model::ANCModel *data) {
  this->_plotWidget->setSignal(data->inverted, data->original);
}
}
}
}
}