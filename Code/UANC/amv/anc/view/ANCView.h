/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ANCVIEW_H
#define UANC_ANCVIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/SignalModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>

namespace uanc {
namespace amv {
namespace anc {
namespace view {

/** \brief Represents an ANCView.
 *
 * This represents a general ANCView. It operates on an ANCModel. It only displays a simple
 * plot of the the inverted signal. It is a specialization of the more general AlgorithmView.
 */
class ANCView : public uanc::amv::AlgorithmView<model::ANCModel> {

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
  void setData(model::ANCModel *data) final;

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

#endif //UANC_ANCVIEW_H
