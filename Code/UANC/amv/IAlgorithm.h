//
// Created by markus on 16.01.17.
//

#ifndef UANC_IALGORITHM_H
#define UANC_IALGORITHM_H

#include "IAlgorithmView.h"
#include "SignalModel.h"

namespace uanc { namespace amv {

/** \brief This can be used to implement an algorithm
 *
 * This class can be used to implement an algorithm.
 */
class IAlgorithm {

 public:

  /** \brief Can be used to clone the algorithm.
   *
   * This can be used to clone the algorithm
   * @return The cloned algorithm
   */
  virtual IAlgorithm *clone() = 0;

  /** \brief This passes back the algorithm view.
   *
   * fills the view with the desired content.
   */
  virtual void fillView() = 0;

  /** \brief This should be implemented by the subclasses.
   *
   * It should pass back an appropriate Name for this algorithm
   *
   * @return the name of this algorithm.
   *
   */
  virtual std::string getName() = 0;

  /** \brief Represents the view itself.
   *
   * Represents the view itself
   * @return The ready created build.
   */
  virtual IAlgorithmView *getView() = 0;

  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
  virtual void process(uanc::amv::SignalModel *input) = 0;
};
}}

#endif //UANC_IALGORITHM_H
