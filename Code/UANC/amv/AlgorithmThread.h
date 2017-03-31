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

#ifndef CODE_UANC_AMV_ALGORITHMTHREAD_H_
#define CODE_UANC_AMV_ALGORITHMTHREAD_H_

#include <QThread>
#include <memory>
#include "IAlgorithm.h"

namespace uanc {
namespace amv {

/** \brief Represents an algorithm thread.
 *
 * This thread basically executes the given task, and connects appropriately
 * to the desired functions.
 */
class AlgorithmThread : public QThread {
Q_OBJECT public slots:

  /** \brief Can be used to set an algorithm.
   *
   * This method takes a pointer and saves it internally, to actually know
   * which algorithm to use for the operation.
   *
   * @param algorithm The Algorithm to use.
   * @param model The Model to invert.
   */
  void
  setAlgorithm(IAlgorithm *algorithm, std::shared_ptr<InvertedModel> model) {
    this->_algorithm = algorithm;
    this->_model = model;
  }

 private:
  /** Holds a pointer to the algorithm. */
  IAlgorithm *_algorithm = nullptr;
  std::shared_ptr<InvertedModel> _model;

 protected:
  /** \brief Ru method of this thread.
   *
   * This method does the running of the algorithm.
   */
  void
  run() final {
    _algorithm->process(_model);
    emit algorithmFinished();
  }

 signals:

  /** Gets called when the algorithm is finished. */
  void
  algorithmFinished();
};
}  // namespace amv
}  // namespace uanc

#endif  // CODE_UANC_AMV_ALGORITHMTHREAD_H_
