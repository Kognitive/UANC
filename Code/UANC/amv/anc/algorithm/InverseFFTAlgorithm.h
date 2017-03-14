/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_INVERSEFFTALGORITHM_H
#define UANC_INVERSEFFTALGORITHM_H

#include <complex>
#include <Code/libs/aquila/source/SignalSource.h>
#include <Code/libs/aquila/transform/FftFactory.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/UANC/amv/anc/view/ANCView.h>
#include <Code/UANC/util/PerformanceMeasure.h>
#include <Code/UANC/amv/anc/view/PMView.h>
#include "ANCAlgorithm.h"

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

using namespace uanc::amv::anc;
using namespace uanc::util;

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

    //const std::size_t SIZE2 = ;
    unsigned int sampleFreqr = inr->getSampleFrequency();

    std::shared_ptr<PerformanceMeasure<>> measurement (new PerformanceMeasure<>());
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

    // --------------------------------- Left Channel ------------------------------------------------

    // copy data to in
    auto in = data->left_channel;

    // map the input signal to a valid sample
    const std::size_t SIZE = 524288;
    //const std::size_t SIZE2 = ;
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

    this->getModel()->inverted = std::shared_ptr<SignalModel>(new InvertedModel);
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

}
}
}
}
#endif //UANC_INVERSEFFTALGORITHM_H
