//
// Created by daniel on 28.01.17.
//

#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/gui/PMWidget.h>
#include "PMView.h"

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
  if (this->_widget == nullptr) {
    // create the widgets for the view
    this->_plotWidget = std::unique_ptr<uanc::gui::PlotWidget>(new uanc::gui::PlotWidget());
    this->_treeview = std::unique_ptr<uanc::gui::PMWidget>(new uanc::gui::PMWidget());
    // set horizontal layout
    this->_widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_plotWidget.get());
    layout->addWidget(_treeview.get());
    this->_widget->setLayout(layout);
    this->_plotWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
void PMView::setData(model::ANCModel *signalData) {
  this->_plotWidget->setSignal(signalData->inverted);
  this->_treeview->setData(signalData->defaultRegister.getCustomMeasurements());

}
}
}
}
}