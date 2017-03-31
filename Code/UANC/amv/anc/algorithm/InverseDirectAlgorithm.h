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

#ifndef CODE_UANC_AMV_ANC_ALGORITHM_INVERSEDIRECTALGORITHM_H_
#define CODE_UANC_AMV_ANC_ALGORITHM_INVERSEDIRECTALGORITHM_H_

#include <memory>
#include <string>
#include "Code/UANC/amv/anc/model/ANCModel.h"
#include "Code/UANC/amv/anc/view/ANCView.h"
#include "Code/UANC/amv/anc/view/PMView.h"
#include "Code/UANC/util/PerformanceMeasure.h"
#include "ANCAlgorithm.h"


namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

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
  void invert(std::shared_ptr<InvertedModel> in) {
    std::shared_ptr<uanc::util::PerformanceMeasure<>> measurement(
        new uanc::util::PerformanceMeasure<>());

    // Start measurement for the inversion
    measurement->start(this->getName());
    measurement->startSubMeasure("Inversion Left Channel");
    // creates a new shared pointer containing the inverted signal
    auto inverted = new SignalModel();
    inverted->left_channel = std::shared_ptr<Aquila::SignalSource>(
        new Aquila::SignalSource(*in->left_channel.get()));
    inverted->left_channel->operator*=(-1);

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();
    measurement->startSubMeasure("Inversion Right Channel");
    inverted->right_channel = std::shared_ptr<Aquila::SignalSource>(
        new Aquila::SignalSource(*in->right_channel.get()));
    inverted->right_channel->operator*=(-1);

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();
    measurement->stop();
    this->getModel()->defaultRegister.registerCustomMeasurement(measurement);

    std::shared_ptr<SignalModel> out(inverted);

    this->getModel()->left_channel = in->left_channel;
    this->getModel()->right_channel = in->right_channel;
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
    return new view::PMView();
  }
};

}  // namespace algorithm
}  // namespace anc
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ANC_ALGORITHM_INVERSEDIRECTALGORITHM_H_
