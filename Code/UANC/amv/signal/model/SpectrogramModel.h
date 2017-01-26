/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SPECTROGRAMMODEL_H
#define UANC_SPECTROGRAMMODEL_H

#include <Code/UANC/amv/SignalModel.h>
#include <Code/UANC/amv/SignalModel.h>
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
class SpectrogramModel : public uanc::amv::SignalModel {
 public:

  /** \brief Holds the spectrum.
   *
   * This field holds the spectrum of the original signal.
   */
  std::shared_ptr<Aquila::Spectrogram> spectrum;
};

}
}
}
}
#endif //UANC_SPECTROGRAMMODEL_H
