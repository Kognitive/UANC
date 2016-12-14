/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "Algorithm.h"

namespace uanc { namespace algorithm {

  /** \brief Represents the execution of the algorithm.
  *
  * This method must be implemented by deriving algorithms, so it can
  * actually be used in the framework.
  *
  * @return the processed vector itself.
  */
  std::shared_ptr<Aquila::SignalSource> Algorithm::process() {

    if (!init) {
      throw std::runtime_error("There was no execution with parameters before");
    }

    return _result;
  }

  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
   std::shared_ptr<Aquila::SignalSource> Algorithm::process(std::shared_ptr<Aquila::SignalSource> input) {

    if (!init) {
      _result = this->execute(input);
      init = true;
    }

    return _result;
   }

  /** \brief This can get the model of the algorithm model.
   *
   * This returns the model of this algorithm.
   * @return The model of this algorithm.
   */
  void Algorithm::fillView() {
    if (this->_builtView == nullptr) {
      throw new std::runtime_error("View wasn't built");
    }

    if (this->_builtModel == nullptr) {
      this->_builtModel = this->constructModel();
      this->_builtModel->samples = this->process();
    }

    this->_builtView->setData(this->_builtModel);
  }

  /** \brief Represents the view itself.
   *
   * Represents the view itself
   * @return The ready created build.
   */
  uanc::gui::interfaces::IAlgorithmView* Algorithm::getView() {
    if (this->_builtView == nullptr) {
      this->_builtView = this->constructView();
    }
    return this->_builtView;
  }
}}