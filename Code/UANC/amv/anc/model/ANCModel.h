/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ANCMODEL_H
#define UANC_ANCMODEL_H

#include <Code/UANC/amv/SignalModel.h>
#include <memory>
#include <Code/UANC/util/PerformanceMeasure.h>

namespace uanc {
namespace amv {
namespace anc {
namespace model {

using namespace uanc::util;

/** \brief This is an ANCModel.
 *
 * This model gets derived from the SignalModel. It adds a field containing
 * the inverted signal to the original signal in SignalModel.
 */
class ANCModel : public uanc::amv::SignalModel {
 public:

  /** \brief Holds the inverted signal.
   *
   * This field gets used, to save the inverted signal, in addition to
   * the original signal, which is placed in the parent class SignalModel.
   */
  std::shared_ptr<Aquila::SignalSource> inverted;

};

}
}
}
}
#endif //UANC_ANCMODEL_H
