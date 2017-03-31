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

#ifndef CODE_UANC_AMV_ANC_ALGORITHM_INVERSEFFTALGORITHM_H_
#define CODE_UANC_AMV_ANC_ALGORITHM_INVERSEFFTALGORITHM_H_

#include <complex>
#include <memory>
#include <string>
#include <vector>
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/libs/aquila/transform/FftFactory.h"
#include "Code/UANC/amv/anc/model/ANCModel.h"
#include "Code/UANC/amv/anc/view/ANCView.h"
#include "Code/UANC/util/PerformanceMeasure.h"
#include "Code/UANC/amv/anc/view/PMView.h"
#include "ANCAlgorithm.h"

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

/** \brief FFT inversion algorithm.
 *
 * This class represents a fft inversion algorithm. It simply transformes the data in the fourier
 * room, inverts it and passed it back.
 */
class InverseFFTAlgorithm : public ANCAlgorithm<model::ANCModel> {
 public:
  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  std::string getName() final { return "Inverse FFT"; };

  /** \brief Inverts the input signal.
   *
   * This is actually the heart of an ANC algorithm inside of this application. It takes
   * an input model and processes it. Besides it should save its data inside the model
   * using getModel().
   *
   * @param input The input model containing the original signal.
   */
  void invert(std::shared_ptr<InvertedModel> data) final {
    // copy data to in
    auto inr = data->right_channel;

    // const std::size_t SIZE2 = ;
    unsigned int sampleFreqr = inr->getSampleFrequency();

    std::shared_ptr<uanc::util::PerformanceMeasure<>> measurement(
        new uanc::util::PerformanceMeasure<>());
    measurement->start(this->getName());

    // start measurement for the fast fouier transformation
    measurement->startSubMeasure("Transformation in Fourier Right");

    // choose a fft algorithm
    auto lenr = inr->length();
    auto fftr = Aquila::FftFactory::getFft(inr->length());

    // transform the signal into the fouier space
    Aquila::SpectrumType spectrumr = fftr->fft(inr->toArray());

    // FFT is done. Stop the mesurement
    measurement->stopSubMeasure();

    // Start mesurment for the invertation in fouier space
    measurement->startSubMeasure("Inversion Right");

    // invert the spectrum
    std::transform(
        spectrumr.begin(),
        spectrumr.end(),
        spectrumr.begin(),
        [](Aquila::ComplexType x) { return (x.operator*=(-2)); });

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();

    // start measurement for the back transformation
    measurement->startSubMeasure("Back transformation Right");

    // back transformation of signal from fouier space
    std::shared_ptr<std::vector<double>> xr = fftr->ifft(spectrumr);

    // Back transformation is done. Stop mesurement
    measurement->stopSubMeasure();

    // define output signal
    std::shared_ptr<Aquila::SignalSource> outputSignalr(
        new Aquila::SignalSource(&(*xr)[0], lenr, sampleFreqr));

    this->getModel()->right_channel = inr;

    // --------------------------------- Left Channel ------------------

    // copy data to in
    auto in = data->left_channel;

    // const std::size_t SIZE2 = ;
    unsigned int sampleFreq = in->getSampleFrequency();

    // start measurement for the fast fouier transformation
    measurement->startSubMeasure("Transformation in Fourier Left");

    // choose a fft algorithm
    auto len = in->length();
    auto fft = Aquila::FftFactory::getFft(in->length());

    // transform the signal into the fouier space
    Aquila::SpectrumType spectrum = fft->fft(in->toArray());

    // FFT is done. Stop the mesurement
    measurement->stopSubMeasure();

    // Start mesurment for the invertation in fouier space
    measurement->startSubMeasure("Inversion Left");

    // invert the spectrum
    std::transform(
        spectrum.begin(),
        spectrum.end(),
        spectrum.begin(),
        [](Aquila::ComplexType x) { return (x.operator*=(-2)); });

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();

    // start measurement for the back transformation
    measurement->startSubMeasure("Back transformation Left");

    // back transformation of signal from fouier space
    std::shared_ptr<std::vector<double>> x = fft->ifft(spectrum);

    // Back transformation is done. Stop mesurement
    measurement->stopSubMeasure();

    measurement->stop();
    this->getModel()->defaultRegister.registerCustomMeasurement(measurement);
    // define output signal
    std::shared_ptr<Aquila::SignalSource> outputSignal(
        new Aquila::SignalSource(&(*x)[0], len, sampleFreq));

    this->getModel()->left_channel = in;

    this->getModel()->inverted = std::shared_ptr<SignalModel>(
        new InvertedModel);
    this->getModel()->inverted->left_channel = outputSignal;
    this->getModel()->inverted->right_channel = outputSignalr;
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
    return new InverseFFTAlgorithm();
  }

 protected:
  /** \brief Constructs a view, which can handle an ANCModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created ANCView.
   */
  AlgorithmView<model::ANCModel> *constructView() override {
    return new view::PMView();
  }
};

}  // namespace algorithm
}  // namespace anc
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ANC_ALGORITHM_INVERSEFFTALGORITHM_H_
