//
// Created by markus on 11/25/16.
//

#ifndef UANC_DIRECTINVERSEALGORITHM_H
#define UANC_DIRECTINVERSEALGORITHM_H

#include <Code/UANC/gui/model/AlgorithmModel.h>
#include <Code/UANC/gui/views/AlgorithmView.h>
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
  std::shared_ptr<Aquila::SignalSource> execute(std::shared_ptr<Aquila::SignalSource> in) {
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
 private:
  uanc::gui::model::AlgorithmModel* constructModel() {
    auto model = new uanc::gui::model::AlgorithmModel();
    return model;
  }

  uanc::gui::views::AlgorithmView* constructView() {
    auto view = new uanc::gui::views::AlgorithmView();
    return view;
  }
};

}}

#endif //UANC_DIRECTINVERSEALGORITHM_H
