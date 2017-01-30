/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SPECTROGRAMTRANSFORMATIONALGORITHM_H
#define UANC_SPECTROGRAMTRANSFORMATIONALGORITHM_H

#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/UANC/amv/signal/view/SignalView.h>
#include "Code/libs/aquila/transform/Spectrogram.h"
#include "Code/libs/aquila/source/FramesCollection.h"
#include <Code/UANC/amv/signal/view/SpectrogramView.h>
#include "SignalTransformationAlgorithm.h"

namespace uanc {
namespace amv {
namespace signal {
namespace algorithm {

using namespace uanc::amv::anc;

/** \brief Transforms the view of a signal into a spectrogram.
 *
 * This transformation basically adds some fourier room information to the basis
 * SignalModel.
 */
class SpectrogramTransformationAlgorithm : public SignalTransformationAlgorithm<model::SpectrogramModel> {
 public:

  /** \brief Returns the name of the transformed data representation.
   *
   * Simply passes back the name of the data transformation
   *
   * @return Name of the data transformation
   */
  std::string getName() final { return "Spektogramm"; };

  /** \brief Simply saves the input signal to the output.
   *
   * This method transforms the input signal into a Spectrogram.
   *
   * @param input The input model containing the original signal.
   */
  void transform(SignalModel *in) final {

    //Compute the spectrogram with one frame per Second. This should be enough.

    Aquila::FramesCollection collectionSpectrogram = Aquila::FramesCollection(
        *(in->original), in->original->getSampleFrequency(), 0);

    this->getModel()->spectrum = std::shared_ptr<Aquila::Spectrogram> ( new Aquila::Spectrogram(collectionSpectrogram));
    //The signal in the signal model is unchanged.
    this->getModel()->original = in->original;
  }

  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an copy of the current FourierTransformationAlgorithm. To do so
   * it simply creates a new instance.
   *
   * @return The cloned algorithm.
   */
  Algorithm *clone() final {
    return new SpectrogramTransformationAlgorithm();
  }

 protected:

  /** \brief Constructs a view, which can handle an FourierModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created algorithm view..
   */
  AlgorithmView<model::SpectrogramModel> *constructView() final {
    return new view::SpectrogramView();
  }
};

}
}
}
}

#endif //UANC_IDENTITYTRANSFORMATIONALGORITHM_H
