/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

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

/** \brief Direct inversion algorithm.
 *
 * This class represents a direct inversion algorithm. It simply multiplies every sample
 * by -1 and outputs the final signal. It uses the simplest working model for ANCAlgorithm (ANCModel)
 */
class InverseDirectAlgorithm : public ANCAlgorithm<model::ANCModel> {
 public:

  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  std::string getName() final { return "Inverse Direct"; };

  /** \brief Inverts the input signal.
   *
   * This is actually the heart of an ANC algorithm inside of this application. It takes
   * an input model and processes it. Besides it should save its data inside the model
   * using getModel().
   *
   * @param input The input model containing the original signal.
   */
  void invert(SignalModel *in) final {

    // creates a new shared pointer containing the inverted signal
    auto inverted = new Aquila::SignalSource(*in->left_channel.get());
    inverted->operator*=(-1);
    std::shared_ptr<Aquila::SignalSource> out(inverted);

    this->getModel()->left_channel = in->left_channel;
    this->getModel()->inverted = out;
  }

  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an copy of the current InverseDirectAlgorithm. To do so
   * it simply creates a new instance.
   *
   * @return The cloned algorithm.
   */
  Algorithm *clone() final {
    return new InverseDirectAlgorithm();
  }

 protected:

  /** \brief Constructs a view, which can handle an ANCModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created ANCView.
   */
  AlgorithmView<model::ANCModel> *constructView() final {
    return new view::ANCView();
  }
};

}
}
}
}

#endif //UANC_DIRECTINVERSEALGORITHM_H
