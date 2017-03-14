/*
 * FFTModel.h
 *
 *  Created on: 30.01.2017
 *      Author: vladimir
 */

#ifndef CODE_UANC_AMV_SIGNAL_MODEL_FFTMODEL_H_
#define CODE_UANC_AMV_SIGNAL_MODEL_FFTMODEL_H_

#include <Code/UANC/amv/InvertedModel.h>
#include "Code/libs/aquila/transform/Spectrogram.h"
#include <memory>

namespace uanc {
namespace amv {
namespace signal {
namespace model {

/** \brief This is a model for the transformation of a signal to a spectrogram representation.
 *
 * It used by the FourierTransformationAlgorithm.
 */
class FFTModel : public uanc::amv::InvertedModel {
 public:

  /** \brief Holds the spectrum.
   *
   * This field holds the spectrum of the original signal.
   */
  std::shared_ptr<uanc::amv::InvertedModel> fftSignal;
};

}
}
}
}



#endif /* CODE_UANC_AMV_SIGNAL_MODEL_FFTMODEL_H_ */
