//
// Created by daniel on 28.01.17.
//

#ifndef UANC_PMVIEW_H
#define UANC_PMVIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/SignalModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/gui/PMWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>

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
  void setData(model::ANCModel *signalData) final;

 private:

  /** \brief Holds a reference to the plot widget used inside.
   *
   * This field holds a unqiue reference to the internally used plot widget.
   */
  std::unique_ptr<uanc::gui::PlotWidget> _plotWidget;

/** \brief Holds a reference to the tree view used inside.
 *
 * This field holds a unqiue reference to the internally used tree view.
 */
  std::unique_ptr<uanc::gui::PMWidget> _treeview;

  /** \brief This represents a weak pointer to the constructed QWidget.
   *
   * This holds a reference to the associated QWidget, if there was one created.
   */
  QSplitter *_splitter = nullptr;
};

}
}
}
}
#endif //UANC_PMVIEW_H
