/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_ALGORITHM_H
#define UANC_ALGORITHM_H

#include <memory>
#include <Code/libs/aquila/source/SignalSource.h>
#include <Code/UANC/gui/interfaces/IAlgorithmView.h>
#include <Code/UANC/gui/views/AlgorithmView.h>

namespace uanc { namespace algorithm {

/** \brief This can be used to implement an algorithm
 *
 * This class can be used to implement an algorithm.
 */
class Algorithm {

 public:

  /** \brief This should be implemented by the subclasses.
   *
   * It should pass back an appropriate Name for this algorithm
   *
   * @return the name of this algorithm.
   *
   */
  virtual std::string getName() = 0;

  /** \brief Represents the execution of the algorithm.
  *
  * This method must be implemented by deriving algorithms, so it can
  * actually be used in the framework.
  *
  * @return the processed vector itself.
  */
  std::shared_ptr<Aquila::SignalSource> process();

  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
   std::shared_ptr<Aquila::SignalSource> process(std::shared_ptr<Aquila::SignalSource> input);

  /** \brief Represents the execution of the algorithm.
   *
   * This method must be implemented by deriving algorithms, so it can
   * actually be used in the framework.
   *
   * @return the processed vector itself.
   */
  virtual std::shared_ptr<Aquila::SignalSource> execute(std::shared_ptr<Aquila::SignalSource> input) = 0;

  /** \brief Can be used to clone the algorithm.
   *
   * This can be used to clone the algorithm
   * @return The cloned algorithm
   */
  virtual Algorithm* clone() = 0;


  /** \brief This passes back the algorithm view.
   *
   * fills the view with the desired content.
   */
  void fillView();

  /** \brief Represents the view itself.
   *
   * Represents the view itself
   * @return The ready created build.
   */
  uanc::gui::interfaces::IAlgorithmView* getView();

 private:

  bool init = false;

  std::shared_ptr<Aquila::SignalSource> _result;

  uanc::gui::views::AlgorithmView* _builtView = nullptr;

  uanc::gui::model::AlgorithmModel* _builtModel = nullptr;

 protected:

  virtual uanc::gui::model::AlgorithmModel* constructModel() = 0;

  virtual uanc::gui::views::AlgorithmView* constructView() = 0;
};

}}

#endif //UANC_ALGORITHM_H
