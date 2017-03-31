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

#ifndef CODE_UANC_AMV_ALGORITHMVIEW_H_
#define CODE_UANC_AMV_ALGORITHMVIEW_H_

#include <memory>
#include "IAlgorithmView.h"

namespace uanc {
namespace amv {

/** \brief Basic algorithm associated view.
 *
 * This class basically knows the underlying model due to the passed template
 * parameter. This is essential for a cast free use inside of the application.
 * Also it defines what models are applicable.
 *
 * @tparam inmodel The type of data the model can handle.
 */
template<typename inmodel>
class AlgorithmView : public IAlgorithmView {
  // Static check, whether the correct model is used.
  static_assert(std::is_base_of<InvertedModel, inmodel>::value,
                "You have to use a SignalModel in any AlgorithmView.");

 public:
  /** \brief This method applies the model data.
  *
  * This method simply takes the passed data and places it inside of the
  * view at the appropriate places.
  *
  * @param data The applied data.
  */
  virtual void setData(std::shared_ptr<inmodel> data) = 0;
};

}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ALGORITHMVIEW_H_
