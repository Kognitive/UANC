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
  void transform(std::shared_ptr<uanc::amv::InvertedModel> in) final {

    this->getModel()->fftSignal = std::shared_ptr<InvertedModel>(new InvertedModel());

    // ------------------------- Left Channel Normal --------------------------------

    //Compute the FFT of the signal
    // choose a fft algorithm
    auto fftl = (in->inverted != NULL) ?
                Aquila::FftFactory::getFft(in->inverted->left_channel->length())
                : Aquila::FftFactory::getFft(in->left_channel->length());

    auto complexFftSignall = (in->inverted != NULL) ?
                             fftl->fft(in->inverted->left_channel->toArray())
                             : fftl->fft(in->left_channel->toArray());

    std::vector<double> aboluteSpectruml;

    //Compute the absolute values of the left_spectrum
    for (int i = 0; i < complexFftSignall.size(); ++i) {
      aboluteSpectruml.push_back(std::abs(complexFftSignall[i]));
    }
    this->getModel()->fftSignal->left_channel = std::shared_ptr<
        Aquila::SignalSource>(new Aquila::SignalSource(aboluteSpectruml));
    this->getModel()->fftSignal->left_channel->setSampleFrequency(in->left_channel->getSampleFrequency());

    // ------------------------- Right Channel Normal --------------------------------

    //The signal in the signal model is unchanged.
    this->getModel()->right_channel = in->right_channel;

    //Compute the FFT of the signal
    // choose a fft algorithm
    auto fftr = (in->inverted != NULL) ?
                Aquila::FftFactory::getFft(in->inverted->right_channel->length())
                : Aquila::FftFactory::getFft(in->right_channel->length());

    auto complexFftSignalr = (in->inverted != NULL) ?
                             fftr->fft(in->inverted->right_channel->toArray())
                             : fftr->fft(in->right_channel->toArray());

    std::vector<double> aboluteSpectrumr;

    //Compute the absolute values of the left_spectrum
    for (int i = 0; i < complexFftSignalr.size(); ++i) {
      aboluteSpectrumr.push_back(std::abs(complexFftSignalr[i]));
    }
    this->getModel()->fftSignal->right_channel = std::shared_ptr<
        Aquila::SignalSource>(new Aquila::SignalSource(aboluteSpectrumr));
    this->getModel()->fftSignal->right_channel->setSampleFrequency(in->right_channel->getSampleFrequency());

    //The signal in the signal model is unchanged.
    this->getModel()->right_channel = in->left_channel;
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
