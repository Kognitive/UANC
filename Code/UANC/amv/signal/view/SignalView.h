/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SIGNALVIEW_H
#define UANC_SIGNALVIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/SignalModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>

namespace uanc {
namespace amv {
namespace signal {
namespace view {

/** \brief Represents a SignalView.
 *
 * This represents a general SignalView. It operates on an SignalModel. It basically shows a plot of the
 * original signal.
 */
class SignalView : public uanc::amv::AlgorithmView<uanc::amv::SignalModel> {

 public:

  /** \brief Gets the complete widget.
   *
   * This function is used to retrieve the widget from the view. It gets
   * used for integration the main application. It creates a Plotwidget inside
   * of a QWidget and passes this back.
   *
   * @return The created widget.
   */
  QWidget *getWidget() final;

  /** \brief This method applies the model data.
  *
  * This method simply takes the passed data and places it inside of the
  * view at the appropriate places.
  *
  * @param data The applied data.
  */
  void setData(uanc::amv::SignalModel *data) final;

 private:

  /** \brief Holds a reference to the plot widget used inside.
   *
   * This field holds a unqiue reference to the internally used plot widget.
   */
  std::unique_ptr<uanc::gui::PlotWidget> _plotWidget;

  /** \brief This represents a weak pointer to the constructed QWidget.
   *
   * This holds a reference to the associated QWidget, if there was one created.
   */
  QWidget *_widget = nullptr;
};

}
}
}
}

#endif //UANC_SIGNALVIEW_H
