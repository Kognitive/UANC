/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_IALGORITHM_H
#define UANC_IALGORITHM_H

#include "IAlgorithmView.h"
#include "SignalModel.h"

namespace uanc {
namespace amv {

/** \brief General interface for any algorithm.
 *
 * This interface is used in the client code. Therefore it has no
 * knowledge of the underlying model nor the view. It gets used
 * for signal views as well as algorithm views.
 */
class IAlgorithm {

 public:

  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an exact copy of the current instance.
   *
   * @return The cloned algorithm.
   */
  virtual IAlgorithm *clone() = 0;

  /** \brief Fills the view with the data.
   *
   * This method fills the view with some data. The implementation
   * itself happens in a subclass.
   */
  virtual void fillView() = 0;

  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  virtual std::string getName() = 0;

  /** \brief Gets a reference to the associated view.
   *
   * A view has to be created in this method, or alternatively
   * an already created view can be returned.
   *
   * @return The associated view.
   */
  virtual IAlgorithmView *getView() = 0;

  /** \brief Processes the input signal model.
   *
   * This method processes the signal model passed into this function.
   * There might be some created data during the processing stage.
   *
   * \param[in] input The input model of the signal.
   */
  virtual void process(uanc::amv::SignalModel *input) = 0;
};
}
}

#endif //UANC_IALGORITHM_H
