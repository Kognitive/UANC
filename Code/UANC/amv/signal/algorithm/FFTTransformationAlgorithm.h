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

    //Create an pointer vector for the in-and output
    std::vector<std::shared_ptr<Aquila::SignalSource>> outChannels{
        this->getModel()->fftSignal->left_channel, this->getModel()->fftSignal
            ->right_channel};

    auto inLeftChannel = (!in->inverted) ?
                         in->left_channel :
                         in->inverted->left_channel;

    auto inRightChannel = (!in->inverted) ?
                          in->right_channel :
                          in->inverted->right_channel;
    std::vector<std::shared_ptr<Aquila::SignalSource>> inChannels{inLeftChannel, inRightChannel};


    //Invert in the Fourier space in both channels, iterate over all channels
    for (int i = 0; i < inChannels.size(); ++i) {
      auto &outChannel = outChannels[i];
      auto inChannel = inChannels[i];

      //Compute the FFT of the signal
      // choose a fft algorithm
      auto fftl = Aquila::FftFactory::getFft(inChannel->length());

      auto complexFftSignal = fftl->fft(inChannel->toArray());

      std::vector<double> aboluteSpectrum;
      //Compute the absolute values of the spectrum
      for (int i = 0; i < complexFftSignal.size(); ++i) {
        aboluteSpectrum.push_back(std::abs(complexFftSignal[i]));
      }

      outChannel = std::shared_ptr<
          Aquila::SignalSource>(new Aquila::SignalSource(aboluteSpectrum));

      outChannel->setSampleFrequency(inChannel->getSampleFrequency());

    }

    this->getModel()->fftSignal->left_channel = outChannels[0];
    this->getModel()->fftSignal->right_channel = outChannels[1];

    //The signal in the signal model is unchanged.
    this->getModel()->left_channel = in->left_channel;
    this->getModel()->right_channel = in->right_channel;
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
