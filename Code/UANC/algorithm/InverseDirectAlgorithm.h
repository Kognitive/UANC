//
// Created by markus on 11/25/16.
//

#ifndef UANC_DIRECTINVERSEALGORITHM_H
#define UANC_DIRECTINVERSEALGORITHM_H

#include "Algorithm.h"

namespace uanc { namespace algorithm {

class InverseDirectAlgorithm : public Algorithm {
 public:
  /** \brief Represents the execution of the direct inverse algorithm.
   *
   * This method should take a vector of size n from the type SignalSource and outputs
   * a vector of size n, also of type SignalSource. Note that the output should be the inverted
   * signal using the direct inverse algorithm. Which basically means, to mirror the samples
   *
   * @return the processed vector itself.
   */
  std::vector<std::shared_ptr<Aquila::SignalSource>> execute(std::vector<std::shared_ptr<Aquila::SignalSource>>) {
    //TODO Direct Inverse anwenden
  }
};

}}

#endif //UANC_DIRECTINVERSEALGORITHM_H
