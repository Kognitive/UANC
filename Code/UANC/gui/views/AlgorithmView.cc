//
// Created by markus on 12/12/16.
//
#include "AlgorithmView.h"

namespace uanc {namespace gui {namespace views {

  /** \brief Should be publically constructable.
   *
   * Simple constructor for creating such an object.
   */
  AlgorithmView::AlgorithmView() {

  }

  /** \brief Builds the shared widget.
   *
   * The shared widget represents the shared widget, which
   * is basically the same over all tabs.
   *
   * @return The created shared widget.
   */
  QWidget* AlgorithmView::buildSharedWidget() {

    // intialize the q custom plot and return the pointer to it.
    this->_qCustomPlot = std::unique_ptr<QCustomPlot>(new QCustomPlot());
    return _qCustomPlot.get();
  }

  /** \brief Function to build the uniqueWidget.
   *
   * This has to be overriden in order to build the unique widget. When the standard
   * implementation is used, there will be no element added.
   *
   * @return The unique widget, created as a qwidget.
   */
  QWidget* AlgorithmView::buildUniqueWidget() {
    return nullptr;
  }

  /** \brief gets the complete widget.
   *
   * This function is used to retrieve the complete widget.
   *
   * @return The ready constructed and loaded widget.
   */
  QWidget* AlgorithmView::getWidget() {
    if (this->_widget == nullptr) {
      auto unique = this->buildUniqueWidget();

      // check if unique does not exist, if not pass down
      // the shared widget
      if (unique == nullptr) {
        this->_widget = this->buildSharedWidget();
      }

      else {

        // otherwise create a two column widget layout
        this->_widget = new QWidget();

        // create the hbox layout and add the shared and the unique widget.
        QHBoxLayout *hlayout = new QHBoxLayout();

        hlayout->addWidget(this->buildSharedWidget());
        hlayout->addWidget(this->buildUniqueWidget());

        // set the correct layout options
        this->_widget->setLayout(hlayout);
      }

    }

    // return the created pointer
    return this->_widget;
  }

  /** \brief Sets the shared data for the algorithm model.
   *
   * This can be used to set the shared data in form of an
   * algorithm model inside of the view. Hence this class
   * has to keep track which data to apply on which position.
   *
   * @param data The data to display in the gui.s
   */
  void AlgorithmView::setSharedData(model::AlgorithmModel* data) {
    uanc::util::tools::QCustomPlotAdapter::plotSignal(data->samples, this->_qCustomPlot.get());
  }

  /** \brief This represents the unique data.
   *
   * This has to be overriden in order to display the data in one
   * specififc way.
   *
   * @param data The data to apply to this view.
   */
  void AlgorithmView::setUniqueData(model::AlgorithmModel* data) {

  }

  /** \brief This method sets the overall data.
   *
   * Can be used to set the overall data.
   *
   * @param data The data to insert into the system.
   */
  void AlgorithmView::setData(model::AlgorithmModel* data) {
    this->setSharedData(data);
    this->setUniqueData(data);
  }
}}}