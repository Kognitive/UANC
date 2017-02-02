/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SIGNALMODEL_H
#define UANC_SIGNALMODEL_H

#include <Code/libs/aquila/source/SignalSource.h>
#include "Code/UANC/amv/PerformanceMeasurementRegister.h"
#include <memory>

namespace uanc {
namespace amv {

/** \brief Every model used inside of this application has to be a signal model.
 *
 * This class represents the most general model. It basically contains a field
 * with the original signal. This gets used throughout the whole project.
 */
class SignalModel {

 public:

  /** \brief Field holds the original samples.
   *
   * Holds the original samples, which were read from the hard drive.
   */
  std::shared_ptr<Aquila::SignalSource> original;

};

}
}

#endif //UANC_SIGNALMODEL_H
