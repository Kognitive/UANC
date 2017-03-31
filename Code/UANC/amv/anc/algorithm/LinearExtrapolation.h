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

#ifndef CODE_UANC_AMV_ANC_ALGORITHM_LINEAREXTRAPOLATION_H_
#define CODE_UANC_AMV_ANC_ALGORITHM_LINEAREXTRAPOLATION_H_

#include <memory>
#include <string>
#include <vector>

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

class LinearExtrapolation : public ANCAlgorithm<model::ANCModel> {
 public:
  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  std::string getName() final { return "Lineare Extrapolation"; };

  /** \brief Inverts the input signal.
   *
   * This is actually the heart of an ANC algorithm inside of this application. It takes
   * an input model and processes it. Besides it should save its data inside the model
   * using getModel().
   *
   * @param input The input model containing the original signal.
   */
  void invert(std::shared_ptr<InvertedModel> in) final {
      std::shared_ptr <uanc::util::PerformanceMeasure<>>
          measurement(new uanc::util::PerformanceMeasure<>());

      // Start measurement for the inversion
      measurement->start(this->getName());
      measurement->startSubMeasure("Transformation & Inversion Left");

      // creates a new shared pointer containing the inverted signal
      auto invertedApproximated = approximate(in->left_channel.get());

      // Invertation is done. Stop mesurement
      measurement->stopSubMeasure();

      std::shared_ptr <Aquila::SignalSource> out(invertedApproximated);

      this->getModel()->left_channel = in->left_channel;

      // ------------------------------- RIGHT CHANNEL --------------

      measurement->startSubMeasure("Transformation & Inversion Right");

      auto invertedApproximatedr = approximate(in->right_channel.get());

      // Invertation is done. Stop mesurement
      measurement->stopSubMeasure();
      measurement->stop();
      this->getModel()->defaultRegister.registerCustomMeasurement(measurement);

      std::shared_ptr <Aquila::SignalSource> outr(invertedApproximatedr);

      this->getModel()->right_channel = in->right_channel;
      this->getModel()->inverted = std::shared_ptr<InvertedModel>(
          new InvertedModel);


      this->getModel()->inverted->left_channel = out;
      this->getModel()->inverted->right_channel = outr;
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
      return new LinearExtrapolation();
  }

 protected:
  /** \brief Constructs a view, which can handle an ANCModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created ANCView.
   */
  AlgorithmView <model::ANCModel> *constructView() final {
      return new view::PMView();
  }

 private:
  /**
   * This field saves the amount of samples that will be approximated.
   * A factor of 1 is equal to Inverse Direct Algorithm.
   */
  int _extrapolationFactor = 15;

  /** \brief This function computes a approximated inverted signal of the input signal.
   *
   * @param signal The input signal which will be approximated and inverted.
   * @return A new signal which is approximated and inverted.
   */
  Aquila::SignalSource* approximate(Aquila::SignalSource* signal) {
      std::vector<double> approxInvSamples(signal->getSamplesCount());

      double slope;
      for (unsigned int i = 0; i < signal->getSamplesCount(); ++i) {
          if (i % _extrapolationFactor == 0) {
              slope = (i == signal->getSamplesCount() - 1)
                      ? 0.0
                      : signal->sample(i + 1) - signal->sample(i);
              approxInvSamples[i] = - signal->sample(i);
          } else {
              approxInvSamples[i] = - (signal->sample(i - 1) + slope);
          }
      }

      Aquila::SignalSource* approxInvSignal =
          new Aquila::SignalSource(approxInvSamples,
                                   signal->getSampleFrequency());

      return approxInvSignal;
  }
};

}  // namespace algorithm
}  // namespace anc
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ANC_ALGORITHM_LINEAREXTRAPOLATION_H_
