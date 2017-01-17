/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ALGORITHMVIEW_H
#define UANC_ALGORITHMVIEW_H

#include "IAlgorithmView.h"

namespace uanc {
namespace amv {

/** \brief Basic algorithm associated view.
 *
 * This class basically knows the underlying model due to the passed template
 * parameter. This is essential for a cast free use inside of the application.
 * Also it defines what models are applicable.
 *
 * @tparam inmodel The type of data the model can handle.
 */
template<typename inmodel>
class AlgorithmView : public IAlgorithmView {

  // Static check, whether the correct model is used.
  static_assert(std::is_base_of<SignalModel, inmodel>::value, "You have to use a SignalModel in any AlgorithmView.");

 public:

  /** \brief This method applies the model data.
  *
  * This method simply takes the passed data and places it inside of the
  * view at the appropriate places.
  *
  * @param data The applied data.
  */
  virtual void setData(inmodel *data) = 0;
};

}
}

#endif //UANC_ALGORITHMVIEW_H
