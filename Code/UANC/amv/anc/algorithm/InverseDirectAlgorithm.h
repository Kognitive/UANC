//
// Created by markus on 11/25/16.
//

#ifndef UANC_DIRECTINVERSEALGORITHM_H
#define UANC_DIRECTINVERSEALGORITHM_H

#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/UANC/amv/anc/view/ANCView.h>
#include "ANCAlgorithm.h"

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

using namespace uanc::amv::anc;

class InverseDirectAlgorithm : public ANCAlgorithm<model::ANCModel, model::ANCModel> {
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
  void invert(SignalModel *in) override {

    // creates a new shared pointer containing the inverted signal
    auto inverted = new Aquila::SignalSource(in->original->operator*=(-1));
    std::shared_ptr<Aquila::SignalSource> out(inverted);

    this->getModel()->original = in->original;
    this->getModel()->inverted = out;
  }

  /** \brief Can be used to clone the algorithm.
   *
   * This can be used to clone the algorithm
   * @return The cloned algorithm
   */
  Algorithm *clone() override {
    return new InverseDirectAlgorithm();
  }

 protected:

  model::ANCModel *createEmptyModel() override {
    return new model::ANCModel();
  }

  AlgorithmView<model::ANCModel> *constructView() override {
    return new view::ANCView();
  }
};

}
}
}
}

#endif //UANC_DIRECTINVERSEALGORITHM_H
