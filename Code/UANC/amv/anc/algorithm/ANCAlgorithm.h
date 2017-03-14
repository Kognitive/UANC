/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ANCALGORITHM_H
#define UANC_ANCALGORITHM_H

#include <Code/UANC/amv/Algorithm.h>

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

/** \brief Every algorithm used inside has to be derived by this class.
 *
 * This represents an ANCAlgorithm. So every inverting algorithm has to be
 * derived by this. In addition one can specify the data model and the view model.
 * If you want to use only a subset of the data you can specify a view model which is
 * actually a parent of the data model. If there is no view model supplied, they will
 * be handled, as if they are the same
 *
 * @tparam datamodel The data model to use, has to be inherited from viewmodel
 * @tparam viewmodel The view model to use, has to be inherited from ANCModel
 */
template<typename datamodel, typename viewmodel = datamodel>
class ANCAlgorithm : public uanc::amv::Algorithm<viewmodel> {

  // check if the models are correct and applicable.
  static_assert(std::is_base_of<viewmodel, datamodel>::value, "The data model has to be derived from the view model.");
  static_assert(std::is_base_of<model::ANCModel, viewmodel>::value, "The view model has to be derived from ANCModel.");

 protected:

  /** \brief Executed an algorithm with the given input model.
   *
   * This method first all gets an empty model from the deriving class. Afterwards it
   * inverts the signal and passed back the model, which was created during the execution stage.
   *
   * \param[in] input The input model of the signal.
   *
   * \return The created model from the data of the inversion.
   */
  std::shared_ptr<viewmodel> execute(std::shared_ptr<InvertedModel> input) final {
    this->model = std::shared_ptr<datamodel>(new viewmodel());
    auto castedModel = static_cast<std::shared_ptr<model::ANCModel>>(this->model);
    castedModel->defaultRegister.startOverallExecutionMeasurement();
    this->invert(input);
    castedModel->defaultRegister.stopOverallExecutionMeasurement();
    return this->getModel();
  }

  /** \brief Gets a pointer, to access the model of the algorithm.
   *
   * Getter for the model used inside of the algorithm. This pointer
   * can be modified by deriving classes to manipulate the model.
   *
   * @return The pointer to the data model stored inside.
   */
  std::shared_ptr<datamodel> getModel() {
    return this->model;
  }

  /** \brief Inverts the input signal.
   *
   * This is actually the heart of an ANC algorithm inside of this application. It takes
   * an input model and processes it. Besides it should save its data inside the model
   * using getModel().
   *
   * @param input The input model containing the original signal.
   */
  virtual void invert(std::shared_ptr<InvertedModel> input) = 0;

 private:

  /** \brief Field for the model.
   *
   * This field gets used to save a reference to the used model. This is passed
   * back by getModel()
   */
  std::shared_ptr<datamodel> model;
};

}
}
}
}

#endif //UANC_ANCALGORITHM_H
