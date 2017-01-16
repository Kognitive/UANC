/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ALGORITHM_H
#define UANC_ALGORITHM_H

#include "IAlgorithm.h"
#include "AlgorithmView.h"

namespace uanc { namespace amv {

/** \brief This can be used to implement an algorithm
 *
 * This class can be used to implement an algorithm.
 */
template<typename outputmodel>
class Algorithm : public IAlgorithm {

 public:

  /** \brief This passes back the algorithm view.
   *
   * fills the view with the desired content.
   */
  void fillView() override {

    // Do some error checks
    if (!this->executed) {
      throw new std::runtime_error("Algorithm was not executed. You have to call process(SignalModel) first.");
    }

    if (this->_builtView == nullptr) {
      throw new std::runtime_error("View was not built. You have to call getView() first.");
    }

    // simply apply the model to the view
    this->_builtView->setData(this->_builtModel);
  }


  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
  void process(uanc::amv::SignalModel* input) override {

    // check if the algorithm was executed before
    if (executed) {
      throw new std::runtime_error("Algorithm was already executed. You should only call this function once.");
    }

    this->_builtModel = this->execute(input);
    executed = true;
  }


  /** \brief Represents the view itself.
   *
   * Represents the view itself
   * @return The ready created build.
   */
  IAlgorithmView* getView() override {
    if (this->_builtView == nullptr) {
      this->_builtView = this->constructView();
    }
    return this->_builtView;
  }

 protected:

  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
  virtual outputmodel* execute(uanc::amv::SignalModel* input) = 0;

 private:

  bool executed = false;

  AlgorithmView<outputmodel>* _builtView = nullptr;

  outputmodel* _builtModel = nullptr;

 protected:

  virtual AlgorithmView<outputmodel>* constructView() = 0;
};

}}

#endif //UANC_ALGORITHM_H
