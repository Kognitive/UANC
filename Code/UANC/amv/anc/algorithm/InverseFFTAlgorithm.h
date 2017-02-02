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
  void invert(SignalModel *data) final {

    // copy data to in
    auto in = data->original;

    // map the input signal to a valid sample
    const std::size_t SIZE = 524288;
    //const std::size_t SIZE2 = ;
    unsigned int sampleFreq = in->getSampleFrequency();

    std::shared_ptr<PerformanceMeasure<>> measurement (new PerformanceMeasure<>());
    measurement->start(this->getName());

    // start measurement for the fast fouier transformation
    measurement->startSubMeasure("Transformation in Fourier");

    // choose a fft algorithm
    auto len = in->length();
    auto fft = Aquila::FftFactory::getFft(in->length());

    // transform the signal into the fouier space
    Aquila::SpectrumType spectrum = fft->fft(in->toArray());

    // FFT is done. Stop the mesurement
    measurement->stopSubMeasure();

    // Start mesurment for the invertation in fouier space
    measurement->startSubMeasure("Inversion");

    // invert the spectrum
    std::transform(
        spectrum.begin(),
        spectrum.end(),
        spectrum.begin(),
        [](Aquila::ComplexType x) { return (x.operator*=(-2)); });

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();

    // start measurement for the back transformation
    measurement->startSubMeasure("Back transformation");

    // back transformation of signal from fouier space
    std::shared_ptr<std::vector<double>> x = fft->ifft(spectrum);

    // Back transformation is done. Stop mesurement
    measurement->stopSubMeasure();

    measurement->stop();
    this->getModel()->defaultRegister.registerCustomMeasurement(measurement);
    // define output signal
    std::shared_ptr<Aquila::SignalSource> outputSignal(
        new Aquila::SignalSource(&(*x)[0], len, sampleFreq));

    this->getModel()->original = in;
    this->getModel()->inverted = outputSignal;

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
