//
// Created by markus on 12.03.17.
//

#ifndef UANC_SPLINES_H
#define UANC_SPLINES_H

#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/UANC/amv/Algorithm.h>
#include <Code/UANC/amv/anc/view/PMView.h>

#include <armadillo>
#include <list>
#include "ANCAlgorithm.h"

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

using namespace uanc::amv::anc;
using namespace uanc::util;
using namespace arma;

class SplineInterpolation : public ANCAlgorithm<model::ANCModel> {
 public:

  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  std::string getName() final { return "Spline Approximation"; };

  /** \brief Inverts the input signal.
   *
   * This is actually the heart of an ANC algorithm inside of this application. It takes
   * an input model and processes it. Besides it should save its data inside the model
   * using getModel().
   *
   * @param input The input model containing the original signal.
   */
  void invert(std::shared_ptr<InvertedModel> in) final {

    std::shared_ptr<PerformanceMeasure<>> measurement(new PerformanceMeasure<>());

    // define left and right channel
    this->getModel()->left_channel = in->left_channel;
    this->getModel()->right_channel = in->right_channel;

    // create inverted model
    this->getModel()->inverted = std::shared_ptr<InvertedModel>(new InvertedModel);

    // Start measurement for the inversion
    measurement->start(this->getName());
    measurement->startSubMeasure("T&I Left");

    // creates a new shared pointer containing the inverted signal
    auto invertedApproximatedLeft = approximate(in->left_channel.get());

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();
    std::shared_ptr<Aquila::SignalSource> outLeft(invertedApproximatedLeft);

    this->getModel()->inverted->left_channel = outLeft;

    // ------------------------------- RIGHT CHANNEL ----------------------------------

    measurement->startSubMeasure("T&I Right");

    auto invertedApproximatedRight = approximate(in->right_channel.get());

    // Invertation is done. Stop mesurement
    measurement->stopSubMeasure();
    measurement->stop();
    this->getModel()->defaultRegister.registerCustomMeasurement(measurement);

    std::shared_ptr<Aquila::SignalSource> outRight(invertedApproximatedRight);

    this->getModel()->inverted->right_channel = outRight;
  }

  /** \brief Clones the current instance.
   *
   * This is basically the prototype pattern. It gets used to create
   * an copy of the current InverseDirectAlgorithm. To do so
   * it simply creates a new instance.
   *
   * @return The cloned algorithm.
   */
  Algorithm *clone() final {
    return new SplineInterpolation();
  }

 protected:

  /** \brief Constructs a view, which can handle an ANCModel.
   *
   * This view basically display the standard information of the algorithm.
   *
   * @return The created ANCView.
   */
  AlgorithmView <model::ANCModel> *constructView() final {
    return new view::PMView();
  }

 private:


  const size_t POLYNOM_DEGREE = 3;
  const size_t COMBINESAMPLES = 100;

  /** \brief This function computes a approximated inverted signal of the input signal.
   *
   * @param signal The input signal which will be approximated and inverted.
   * @return A new signal which is approximated and inverted.
   */
  Aquila::SignalSource *approximate(const Aquila::SignalSource *signal) {

    // calculate widht between
    const double widthBetween = 1. / signal->getSampleFrequency();

    // reserve vector for result
    std::vector<double> result(signal->getSamplesCount());

    // iterate over all samples, with the given window size.
    size_t i = 0;
    size_t last = i;
    int straight_counter = 0;
    bool first = true;


    int state = 0;
    int counter = 0;
    int dcounter = 0;
    std::list<size_t> indices;

    // start with the pair
    indices.push_back(0);

    while (i < signal->getSamplesCount() - 1) {

      dcounter++;

      // simplw state machine to count local optima and turn points
      switch (state) {

        // Case for going up
        case 0:

          if (signal->sample(i) == signal->sample(i+1)) state = 1;
          if (signal->sample(i) > signal->sample(i+1)) state = 2;
          break;

          // When you got up
        case 1:

          if (signal->sample(i) < signal->sample(i+1)) {
            state = 0;
            counter += 2;
          }
          else if (signal->sample(i) > signal->sample(i+1)) {
            state = 2;
            counter += 1;
          }
          break;

          // When you go down
        case 2:

          if (signal->sample(i) == signal->sample(i+1)) state = 3;
          else if (signal->sample(i) < signal->sample(i+1)) state = 0;
          break;

        case 3:

          // When you got down
          if (signal->sample(i) < signal->sample(i+1)) {
            state = 0;
            counter += 1;
          }
          else if (signal->sample(i) > signal->sample(i+1)) {
            state = 2;
            counter += 2;
          }
          break;
      }

      // if you reached the approximation range of a polynomial
      if (dcounter >= POLYNOM_DEGREE - 1) {
        dcounter = 0;
        indices.push_back(i);
      }

      i++;
    }

    // start with the pair
    indices.push_back(signal->getSamplesCount() - 1);

    // iterate over all pairs of indices.
    for (auto current = indices.begin(), nxt = next(current); nxt != indices.end(); current = nxt, nxt = next(nxt)) {
      // std::cout << (*nxt - *current) << " Samples" << std::endl;
      auto alpha = optimalAlpha(*current, *nxt - 1, *nxt - *current, signal, widthBetween);

      // fill in the values
      for (size_t k = *current; k < *nxt; k++) {
        double x = widthBetween * k;
        double c = 1;
        double y = 0;
        for (int i = 0; i < POLYNOM_DEGREE; i++) {
          y -= c * alpha(i);
          c *= x;
        }
        result[k] = y;
      }
    }


    Aquila::SignalSource* approxInvSignal = new Aquila::SignalSource(result, signal->getSampleFrequency());
    return approxInvSignal;
  }

  colvec optimalAlpha(size_t min, size_t max, size_t samples, const Aquila::SignalSource *signal, double widthBetween) {

    // create t
    colvec t(4);
    t[0] = signal->sample(min);
    t[1] = signal->sample(max);

    // estimate derivative using forward differences
    t[2] = (signal->sample(min + 1) - signal->sample(min));
    t[3] = (signal->sample(max) - signal->sample(max - 1));

    // generate P
    mat P(4,POLYNOM_DEGREE);
    P = fillWithPolynomial(0, widthBetween * min, P);
    P = fillWithPolynomial(1, widthBetween * max, P);
    P = fillWithDerivative(2, widthBetween * min, P);
    P = fillWithDerivative(3, widthBetween * max, P);

    // calculate pseudo inverse
    auto alpha = pinv(P) * t;

    // calculate K
    mat K(samples, POLYNOM_DEGREE);
    colvec Y(samples);

    // iterate and fill
    for (size_t k = min; k <= max; k++) {
      K = fillWithPolynomial((int) (k - min), widthBetween * k, K);
      Y[k - min] = signal->sample(k);
    }

    // find nullspace of P and KB Pseudoinverse
    mat B = null(P, 0);
    mat KB = K * B;
    mat KBP = pinv(K * B);

    // calculate optimal alpha parameters
    mat BKBP = B * KBP;
    mat right = K * alpha;
    mat rightMult = Y - right;
    mat compRight = BKBP * rightMult;
    colvec alphaStar = alpha + compRight;
    return alphaStar;
  }

    mat& fillWithPolynomial(int row, double x, mat &matrix) {
    double c = 1;
    for (int i = 0; i < POLYNOM_DEGREE; i++) {
      matrix(row, i) = c;
      c *= x;
    }
      return matrix;
  }

  mat& fillWithDerivative(int row, double x, mat &matrix) {
    int cLeft = 0;
    double cRight = 0;

    // create first field
    matrix(row,0) = cLeft * cRight;
    cLeft = 1;
    cRight = 1;

    // create rest
    for (int i = 1; i < POLYNOM_DEGREE; i++) {
      matrix(row,i) = cLeft * cRight;
      cLeft++;
      cRight *= x;
    }
    return matrix;
  }

};
}
}
}
}

#endif //UANC_SPLINES_H