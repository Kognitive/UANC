//
// Created by markus on 11/25/16.
//

#ifndef UANC_INVERSEFFTALGORITHM_H
#define UANC_INVERSEFFTALGORITHM_H

#include "Algorithm.h"
#include <Code/UANC/gui/model/FFTModel.h>
#include <Code/UANC/gui/views/FFTView.h>
#include <complex>
#include <Code/libs/aquila/source/SignalSource.h>
#include <Code/libs/aquila/transform/FftFactory.h>

namespace uanc {
namespace algorithm {

class InverseFFTAlgorithm : public Algorithm {
 public:

  /** \brief This should be implemented by the subclasses.
   *
   * It should pass back an appropriate Name for this algorithm
   *
   * @return the name of this algorithm.
   *
   */
  std::string getName() override { return "Inverse FFT"; };

  /** \brief Represents the execution of the inverse fft algorithm.
   *
   * This method should take a vector of size n from the type SignalSource and outputs
   * a vector of size n, also of type SignalSource. Note that the output should be the inverted
   * signal using fft inverse algorithm
   *
   * @return the processed vector itself.
   */
  std::shared_ptr<Aquila::SignalSource> execute(std::shared_ptr<Aquila::SignalSource> in) override {
    // map the input signal to a valid sample
    const std::size_t SIZE = 524288;
    //const std::size_t SIZE2 = in->length();
    auto sampleFreq = in->getSampleFrequency();

    // choose a fft algorithm
    auto fft = Aquila::FftFactory::getFft(SIZE);

    // transform the signal into the fouier space
    Aquila::SpectrumType spectrum = fft->fft(in->toArray());

    // invert the spectrum
    std::transform(
        spectrum.begin(),
        spectrum.end(),
        spectrum.begin(),
        [](Aquila::ComplexType x) { return (x.operator*=(-1)); });

    // back transformation of signal from fouier space
    double x[SIZE];
    fft->ifft(spectrum, x);

    // define output signal
    Aquila::SignalSource *t = new Aquila::SignalSource(x, SIZE);
    t->setSampleFrequency(sampleFreq);
    std::shared_ptr<Aquila::SignalSource> outputSignal(new Aquila::SignalSource(*t));

    return outputSignal;
  }

  /** \brief Can be used to clone the algorithm.
   *
   * This can be used to clone the algorithm
   * @return The cloned algorithm
   */
  Algorithm *clone() override {
    new InverseFFTAlgorithm();
  }
 private:
  uanc::gui::model::AlgorithmModel *constructModel() override {
    auto model = new uanc::gui::model::FFTModel();
    return model;
  }

  uanc::gui::interfaces::IAlgorithmView *constructView() override {
    auto view = new uanc::gui::views::FFTView();
    return view;
  }
};

}}
#endif //UANC_INVERSEFFTALGORITHM_H
