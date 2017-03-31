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

#ifndef CODE_UANC_AMV_INVERTEDMODEL_H_
#define CODE_UANC_AMV_INVERTEDMODEL_H_

#include <memory>
#include "Code/UANC/amv/SignalModel.h"
#include "Code/UANC/util/PerformanceMeasure.h"

namespace uanc {
namespace amv {

/** \brief This is an InvertedModel.
 *
 * This model gets derived from the SignalModel. It adds a field containing
 * the inverted signal to the original signal in SignalModel.
 */
class InvertedModel : public uanc::amv::SignalModel {
 public:
    /** \brief Holds the inverted signal.
     *
     * This field gets used, to save the inverted signal, in addition to
     * the original signal, which is placed in the parent class SignalModel.
     */
    std::shared_ptr<SignalModel> inverted = NULL;
};

}  // namespace amv
}  // namespace uanc
#endif  // CODE_UANC_AMV_INVERTEDMODEL_H_
