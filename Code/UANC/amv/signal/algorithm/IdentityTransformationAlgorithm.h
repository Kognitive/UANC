/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UANC_IDENTITYTRANSFORMATIONALGORITHM_H
#define UANC_IDENTITYTRANSFORMATIONALGORITHM_H

#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/UANC/amv/anc/view/ANCView.h>
#include <Code/UANC/amv/signal/view/SignalView.h>
#include "SignalTransformationAlgorithm.h"

namespace uanc {
namespace amv {
namespace signal {
namespace algorithm {

using namespace uanc::amv::anc;
using namespace uanc::amv;

/** \brief Identity transformation.
 *
 * This transformation basically outputs the same signal which was set as an input. This is neccessary
 * for a good integration inside of the application, because we don't want to differntiate versus direct
 * data or transformed data views.
 */
class IdentityTransformationAlgorithm : public SignalTransformationAlgorithm<InvertedModel> {
 public:

  /** \brief Returns the name of the transformed data representation.
   *
   * Simply passes back the name of the data transformation
   *
   * @return Name of the data transformation
   */
  std::string getName() final { return "Original"; };

  /** \brief Simply saves the input signal to the output.
   *
   * This method just passes back the input model signal. It is only needed for
   * integration purposes.
   *
   * @param input The input model containing the original signal.
   */
  void transform(std::shared_ptr<uanc::amv::InvertedModel> in) final {
    this->getModel()->left_channel = in->left_channel;
    this->getModel()->right_channel = in->right_channel;

    if (in->inverted) {
      this->getModel()->inverted = std::shared_ptr<SignalModel>(new SignalModel);
      this->getModel()->inverted->left_channel = in->inverted->left_channel;
      this->getModel()->inverted->right_channel = in->inverted->right_channel;
    }
  }

  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an copy of the current IdentityTransformationAlgorithm. To do so
   * it simply creates a new instance.
   *
   * @return The cloned algorithm.
   */
  Algorithm *clone() final {
    return new IdentityTransformationAlgorithm();
  }

 protected:

  /** \brief Constructs a view, which can handle an ANCModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created ANCView.
   */
  AlgorithmView<InvertedModel> *constructView() final {
    return new view::SignalView();
  }
};

}
}
}
}

#endif //UANC_IDENTITYTRANSFORMATIONALGORITHM_H
