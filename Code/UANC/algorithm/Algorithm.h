/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ALGORITHM_H
#define UANC_ALGORITHM_H

#include <memory>
#include "Code/libs/aquila/source/SignalSource.h"

namespace uanc { namespace algorithm {

/** \brief This can be used to implement an algorithm
 *
 * This class can be used to implement an algorithm.
 */
class Algorithm {

 public:

  /** \brief This should be implemented by the subclasses.
   *
   * It should pass back an appropriate Name for this algorithm
   *
   * @return the name of this algorithm.
   *
   */
  virtual std::string getName() = 0;

  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
  virtual std::vector<std::shared_ptr<Aquila::SignalSource>> execute(std::vector<std::shared_ptr<Aquila::SignalSource>>) = 0;
};

}}

#endif //UANC_ALGORITHM_H
