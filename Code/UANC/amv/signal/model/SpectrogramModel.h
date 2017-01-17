/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SPECTROGRAMMODEL_H
#define UANC_SPECTROGRAMMODEL_H

#include <Code/UANC/amv/SignalModel.h>
#include <memory>

namespace uanc {
namespace amv {
namespace signal {
namespace model {

/** \brief This is an FourierModel.
 *
 * It basically extends the standard signal model by some FFT related data.
 * It used by the FourierTransformationAlgorithm.
 */
class SpectrogramModel : public uanc::amv::SignalModel {
 public:

  /** \brief Holds the spectrum.
   *
   * This field holds the spectrum of the original signal.
   */
  std::shared_ptr<Aquila::SignalSource> spectrum;
};

}
}
}
}
#endif //UANC_SPECTROGRAMMODEL_H
