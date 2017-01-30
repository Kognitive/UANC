/*
 * FFTTransformationAlgorithm.h
 *
 *  Created on: 30.01.2017
 *      Author: vladimir
 */

#ifndef CODE_UANC_AMV_SIGNAL_ALGORITHM_FFTTRANSFORMATIONALGORITHM_H_
#define CODE_UANC_AMV_SIGNAL_ALGORITHM_FFTTRANSFORMATIONALGORITHM_H_

#include <Code/UANC/amv/signal/algorithm/SignalTransformationAlgorithm.h>
#include <Code/UANC/amv/signal/model/FFTModel.h>
#include <Code/UANC/amv/signal/view/FFTView.h>
#include <Code/libs/aquila/source/SignalSource.h>
#include <Code/libs/aquila/transform/FftFactory.h>

namespace uanc {
namespace amv {
namespace signal {
namespace algorithm {

/** \brief Transforms the view of a signal into Fourier space using FFT.
 *
 */
class FFTTransformationAlgorithm :
    public amv::signal::algorithm::SignalTransformationAlgorithm<
        model::FFTModel> {
 public:

  /** \brief Returns the name of the transformed data representation.
   *
   * Simply passes back the name of the data transformation
   *
   * @return Name of the data transformation
   */
  std::string getName() final {
    return "FFT";
  }

  /** \brief Simply saves the input signal to the output.
   *
   * This method transforms the input signal into Fourier space and writes it into the model.
   *
   * @param input The input model containing the original signal.
   */
  void transform(SignalModel *in) final {

    //Compute the FFT of the signal
    // choose a fft algorithm
    auto fft = Aquila::FftFactory::getFft(in->original->length());

    auto complexFftSignal = fft->fft(in->original->toArray());

    std::vector<double> aboluteSpectrum;

    //Compute the absolute values of the spectrum
    for (int i = 0; i < complexFftSignal.size(); ++i) {
      aboluteSpectrum.push_back(std::abs(complexFftSignal[i]));
    }
    this->getModel()->fftSignal = std::shared_ptr<
        Aquila::SignalSource>(new Aquila::SignalSource(aboluteSpectrum));

    //The signal in the signal model is unchanged.
    this->getModel()->original = in->original;
  }

  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an copy of the current FFTTransformationAlgorithm. To do so
   * it simply creates a new instance.
   *
   * @return The cloned algorithm.
   */
  Algorithm *clone() final {
    return new FFTTransformationAlgorithm();
  }

 protected:

  /** \brief Constructs a view, which can handle an FourierModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created algorithm view..
   */
  AlgorithmView<model::FFTModel> *constructView() final {
    return new view::FFTView();
  }

};

}
}
}
}/* namespaces */

#endif /* CODE_UANC_AMV_SIGNAL_ALGORITHM_FFTTRANSFORMATIONALGORITHM_H_ */
