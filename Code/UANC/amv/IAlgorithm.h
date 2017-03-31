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

#ifndef CODE_UANC_AMV_IALGORITHM_H_
#define CODE_UANC_AMV_IALGORITHM_H_

#include <memory>
#include <string>
#include "IAlgorithmView.h"
#include "Code/UANC/amv/anc/model/ANCModel.h"

namespace uanc {
namespace amv {

/** \brief General interface for any algorithm.
 *
 * This interface is used in the client code. Therefore it has no
 * knowledge of the underlying model nor the view. It gets used
 * for signal views as well as algorithm views.
 */
class IAlgorithm {
 public:
  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an exact copy of the current instance.
   *
   * @return The cloned algorithm.
   */
  virtual IAlgorithm *clone() = 0;

  /** \brief Fills the view with the data.
   *
   * This method fills the view with some data. The implementation
   * itself happens in a subclass.
   */
  virtual void fillView() = 0;

  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  virtual std::string getName() = 0;

  /** \brief Gets a reference to the associated view.
   *
   * A view has to be created in this method, or alternatively
   * an already created view can be returned.
   *
   * @return The associated view.
   */
  virtual IAlgorithmView *getView() = 0;

  /** \brief Processes the input signal model.
   *
   * This method processes the signal model passed into this function.
   * There might be some created data during the processing stage.
   *
   * \param[in] input The input model of the signal.
   */
  virtual void process(std::shared_ptr<uanc::amv::InvertedModel> input) = 0;
};
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_IALGORITHM_H_
