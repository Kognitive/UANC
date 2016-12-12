//
// Created by markus on 11/25/16.
//

#ifndef UANC_DIRECTINVERSEALGORITHM_H
#define UANC_DIRECTINVERSEALGORITHM_H

#include "Algorithm.h"

namespace uanc { namespace algorithm {

class InverseDirectAlgorithm : public Algorithm {
 public:

  /** \brief This should be implemented by the subclasses.
   *
   * It should pass back an appropriate Name for this algorithm
   *
   * @return the name of this algorithm.
   *
   */
  std::string getName() override { return "Inverse Direct"; };

  /** \brief Represents the execution of the direct inverse algorithm.
   *
   * This method should take a vector of size n from the type SignalSource and outputs
   * a vector of size n, also of type SignalSource. Note that the output should be the inverted
   * signal using the direct inverse algorithm. Which basically means, to mirror the samples
   *
   * @return the processed vector itself.
   */
  std::vector<std::shared_ptr<Aquila::SignalSource>> execute(std::vector<std::shared_ptr<Aquila::SignalSource>> in) {
    return in;
  }

  /** \brief Can be used to clone the algorithm.
   *
   * This can be used to clone the algorithm
   * @return The cloned algorithm
   */
  Algorithm* clone() {
    return new InverseDirectAlgorithm();
  }
};

}}

#endif //UANC_DIRECTINVERSEALGORITHM_H
