//
// Created by markus on 12/12/16.
//

#ifndef UANC_ANCVIEW_H
#define UANC_ANCVIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/SignalModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>

namespace uanc { namespace amv { namespace anc { namespace view {

/** \brief Represents an algorithm view, which can be used inside
 * of the application.
 *
 * This represents a algorithm view which can be used with an appropriate model.
 */
class ANCView : public uanc::amv::AlgorithmView<model::ANCModel> {

 public:

  /** \brief Should be publically constructable.
   *
   * Simple constructor for creating such an object.
   */
  ANCView();

  /** \brief Builds the shared widget.
   *
   * The shared widget represents the shared widget, which
   * is basically the same over all tabs.
   *
   * @return The created shared widget.
   */
  QWidget* buildSharedWidget();

  /** \brief Function to build the uniqueWidget.
   *
   * This has to be overriden in order to build the unique widget. When the standard
   * implementation is used, there will be no element added.
   *
   * @return The unique widget, created as a qwidget.
   */
  virtual QWidget* buildUniqueWidget();

  /** \brief gets the complete widget.
   *
   * This function is used to retrieve the complete widget.
   *
   * @return The ready constructed and loaded widget.
   */
  QWidget* getWidget();

  /** \brief Sets the shared data for the algorithm model.
   *
   * This can be used to set the shared data in form of an
   * algorithm model inside of the view. Hence this class
   * has to keep track which data to apply on which position.
   *
   * @param data The data to display in the gui.s
   */
  void setSharedData(model::ANCModel* data);

  /** \brief This represents the unique data.
   *
   * This has to be overriden in order to display the data in one
   * specififc way.
   *
   * @param data The data to apply to this view.
   */
  virtual void setUniqueData(model::ANCModel* data);

  /** \brief This method sets the overall data.
   *
   * Can be used to set the overall data.
   *
   * @param data The data to insert into the system.
   */
   void setData(model::ANCModel* data) final;

 private:

  /** \brief Contains the plot of this algorithm view. */
  std::unique_ptr<uanc::gui::PlotWidget> _plotWidget;

  /** \brief This represents a weak pointer as an image.
   *
   * This can be used as a weak pointer.
   */
  QWidget* _widget = nullptr;
};

}}}}



#endif //UANC_ANCVIEW_H
