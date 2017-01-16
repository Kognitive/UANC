//
// Created by markus on 16.01.17.
//

#ifndef UANC_ALGORITHMVIEW_H
#define UANC_ALGORITHMVIEW_H

#include "IAlgorithmView.h"

namespace uanc { namespace amv {

template <class model>
class AlgorithmView : public IAlgorithmView {

 public:

  /** \brief This method sets the overall data.
  *
  * Can be used to set the overall data.
  *
  * @param data The data to insert into the system.
  */
  virtual void setData(model* data) = 0;
};

}}

#endif //UANC_ALGORITHMVIEW_H
