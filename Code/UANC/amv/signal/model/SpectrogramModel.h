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

#ifndef UANC_SPECTROGRAMMODEL_H
#define UANC_SPECTROGRAMMODEL_H

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
class SpectrogramModel : public uanc::amv::InvertedModel {
 public:

  /** \brief Holds the spectrum.
   *
   * This field holds the spectrum of the original signal.
   */
  std::shared_ptr<Aquila::Spectrogram> left_spectrum;

  /** \brief Holds the spectrum.
   *
   * This field holds the spectrum of the original signal.
   */
  std::shared_ptr<Aquila::Spectrogram> right_spectrum;
};

}
}
}
}
#endif //UANC_SPECTROGRAMMODEL_H
