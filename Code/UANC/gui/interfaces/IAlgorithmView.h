//
// Created by markus on 12/14/16.
//

#ifndef UANC_IALGORITHMVIEW_H
#define UANC_IALGORITHMVIEW_H

#include <QtWidgets/QWidget>
#include <Code/UANC/gui/model/AlgorithmModel.h>

namespace uanc { namespace gui { namespace interfaces {

/** \brief Represents an algorithm view, which can be used inside
 * of the application.
 *
 * This represents a algorithm view which can be used with an appropriate model.
 */
class IAlgorithmView {

 public:

  /** \brief gets the complete widget.
   *
   * This function is used to retrieve the complete widget.
   *
   * @return The ready constructed and loaded widget.
   */
  virtual QWidget* getWidget() = 0;

   /** \brief This method sets the overall data.
   *
   * Can be used to set the overall data.
   *
   * @param data The data to insert into the system.
   */
   virtual void setData(model::AlgorithmModel* data) = 0;
};

}}}

#endif //UANC_IALGORITHMVIEW_H
