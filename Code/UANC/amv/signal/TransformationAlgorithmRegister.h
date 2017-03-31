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

#ifndef UANC_TRANSFORMATIONALGORITHMREGISTER_H
#define UANC_TRANSFORMATIONALGORITHMREGISTER_H

#include <memory>
#include "Code/UANC/amv/signal/algorithm/IdentityTransformationAlgorithm.h"
#include "Code/UANC/amv/signal/algorithm/SpectrogramTransformationAlgorithm.h"
#include "Code/UANC/amv/signal/algorithm/FFTTransformationAlgorithm.h"

namespace uanc {
namespace amv {
namespace signal {

// include namespace of the algorithms to support readability.
using namespace signal::algorithm;

/** \brief This class is used to retain a list of all transformation.
 *
 * This class represents the extendability point for all transformations and data representations
 * If you have implemented another representation simply register it inside of this class and it
 * will automatically be integrated in the application.
 */
class TransformationAlgorithmRegister {
 public:

  /** \brief Supply all registered transformation.
   *
   * This method basically returns a list of all transformations registered inside of the application.
   * To add you new implemented one, simply add it to the list at the bottom.
   *
   * @return A vector containing a prototype of all transformations.
   */
  static std::shared_ptr<std::vector<uanc::amv::IAlgorithm *>> getTransformations() {

    // simply create an empty vector
    auto lst = std::shared_ptr<std::vector<uanc::amv::IAlgorithm *>>(new std::vector<uanc::amv::IAlgorithm *>());

    // --------------------------------------
    // Here you can register your algorithms:
    // --------------------------------------

    lst->push_back(new IdentityTransformationAlgorithm());
    lst->push_back(new SpectrogramTransformationAlgorithm());
    lst->push_back(new FFTTransformationAlgorithm());
    // --------------------------------------

    return lst;
  }
};
}
}
}

#endif //UANC_TRANSFORMATIONALGORITHMREGISTER_H
