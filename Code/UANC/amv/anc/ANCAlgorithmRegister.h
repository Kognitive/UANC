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

#ifndef CODE_UANC_AMV_ANC_ANCALGORITHMREGISTER_H_
#define CODE_UANC_AMV_ANC_ANCALGORITHMREGISTER_H_

#include <memory>
#include <vector>
#include "Code/UANC/amv/anc/algorithm/InverseDirectAlgorithm.h"
#include "Code/UANC/amv/anc/algorithm/InverseFFTAlgorithm.h"
#include "Code/UANC/amv/anc/algorithm/LinearExtrapolation.h"
#include "Code/UANC/amv/anc/algorithm/LocallyWeightedRegression.h"
#include "Code/UANC/amv/anc/algorithm/QuinticSplines.h"
#include "Code/UANC/amv/anc/algorithm/PolynomialRegression.h"

namespace uanc {
namespace amv {
namespace anc {

/** \brief This class is used to retain a list of all algorithms.
 *
 * This class represents the extendability point for all algorithms. If you have implemented
 * an algorithm simply register it inside of this class and it will automatically be integrated
 * in the application.
 */
class ANCAlgorithmRegister {
 public:
  /** \brief Supply all registered algorithms.
   *
   * This method basically returns a list of all algorithms registered inside of the application.
   * To add you new implemented one, simply add it to the list at the bottom.
   *
   * @return A vector containing a prototype of all algorithms.
   */
  static std::shared_ptr<std::vector<uanc::amv::IAlgorithm *>> getAlgorithms() {
    // simply create an empty vector
    auto lst = std::shared_ptr<std::vector<uanc::amv::IAlgorithm *>>(
        new std::vector<uanc::amv::IAlgorithm *>());

    // --------------------------------------
    // Here you can register your algorithms:
    // --------------------------------------

    lst->push_back(new anc::algorithm::InverseDirectAlgorithm());
    lst->push_back(new anc::algorithm::InverseFFTAlgorithm());
    lst->push_back(new anc::algorithm::LinearExtrapolation());
    lst->push_back(new anc::algorithm::QuinticSplines());
    lst->push_back(new anc::algorithm::PolynomialRegression());
    lst->push_back(new anc::algorithm::LocallyWeightedRegression());

    // --------------------------------------

    return lst;
  }
};
}  // namespace anc
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ANC_ANCALGORITHMREGISTER_H_
