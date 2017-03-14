/*
 * FFTView.cpp
 *
 *  Created on: 30.01.2017
 *      Author: vladimir
 */

#include <Code/UANC/gui/PlotWidget.h>
#include "FFTView.h"


namespace uanc {
namespace amv {
namespace signal {
namespace view {

using namespace uanc::amv::signal;

/** \brief Gets the complete widget.
 *
 * This function is used to retrieve the widget from the view. It gets
 * used for integration the main application. It creates a Plotwidget inside
 * of a QWidget and passes this back. Uses the singleton pattern to ensure the
 * unique creation of the widget.
 *
 * @return The created widget.
 */
QWidget *FFTView::produceWidget() {

  this->_plotWidget = new uanc::gui::PlotWidget();

  // return the created pointer
  return this->_plotWidget;
}

/** \brief This method applies the model data.
 *
 * This method simply takes the passed data and places it inside of the
 * view at the appropriate places.
 *
 * @param data The applied data.
 */
void FFTView::setData(std::shared_ptr<model::FFTModel> data) {


  this->_plotWidget->setSignal(data->fftSignal);
}

}
}
}
}
