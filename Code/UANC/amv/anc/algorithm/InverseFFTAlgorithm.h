//
// Created by markus on 11/25/16.
//

#ifndef UANC_INVERSEFFTALGORITHM_H
#define UANC_INVERSEFFTALGORITHM_H

#include <complex>
#include <Code/libs/aquila/source/SignalSource.h>
#include <Code/libs/aquila/transform/FftFactory.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/UANC/amv/anc/view/ANCView.h>
#include "ANCAlgorithm.h"

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

using namespace uanc::amv::anc;

class InverseFFTAlgorithm : public ANCAlgorithm<model::ANCModel> {
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
  void invert(SignalModel *data) override {

    // copy data to in
    auto in = data->original;

    // map the input signal to a valid sample
    const std::size_t SIZE = 524288;
    //const std::size_t SIZE2 = ;
    unsigned int sampleFreq = in->getSampleFrequency();

    // choose a fft algorithm
    auto fft = Aquila::FftFactory::getFft(in->length());

    // transform the signal into the fouier space
    Aquila::SpectrumType spectrum = fft->fft(in->toArray());

    // invert the spectrum
    std::transform(
        spectrum.begin(),
        spectrum.end(),
        spectrum.begin(),
        [](Aquila::ComplexType x) { return (x.operator*=(-1)); });

    // back transformation of signal from fouier space
    std::shared_ptr<std::vector<double>>  x = fft->ifft(spectrum);

    // define output signal
    std::shared_ptr<Aquila::SignalSource> outputSignal(
        new Aquila::SignalSource(&(*x)[0], x->size(), sampleFreq));

    this->getModel()->original = in;
    this->getModel()->inverted = outputSignal;
  }

  /** \brief Can be used to clone the algorithm.
   *
   * This can be used to clone the algorithm
   * @return The cloned algorithm
   */
  Algorithm *clone() override {
    return new InverseFFTAlgorithm();
  }

 protected:

  model::ANCModel *createEmptyModel() override {
    return new model::ANCModel();
  }

  AlgorithmView<model::ANCModel> *constructView() override {
    return new view::ANCView();
  }
};

}}}}
#endif //UANC_INVERSEFFTALGORITHM_H
