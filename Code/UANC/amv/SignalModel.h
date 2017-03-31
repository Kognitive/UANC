/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CODE_UANC_AMV_SIGNALMODEL_H_
#define CODE_UANC_AMV_SIGNALMODEL_H_

#include <memory>
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/UANC/amv/PerformanceMeasurementRegister.h"


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
  std::shared_ptr<Aquila::SignalSource> left_channel;

  /** \brief Field holds the right samples.
   *
   * Holds the original samples, which were read from the hard drive.
   */
  std::shared_ptr<Aquila::SignalSource> right_channel;
};

}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_SIGNALMODEL_H_
