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

  // Settings for this algorithm.
  static const size_t POLYNOM_DEGREE = 5;
  static const size_t SAMPLE_BUNCH = 10;

  /** \brief This function computes a approximated inverted signal of the input signal.
   *
   * @param signal The input signal which will be approximated and inverted.
   * @return A new signal which is approximated and inverted.
   */
  Aquila::SignalSource *approximate(const Aquila::SignalSource *signal) {

    // calculate widht between
    const double widthBetween = 1;
    const double normalization = 1;

    // reserve vector for result
    std::vector<double> result(signal->getSamplesCount());

      if (signal->getSamplesCount() > 0) {

        // first of all do some preprocessing, i.e check if the sample count
        // divisible by the bunch size
        size_t remaining = signal->getSamplesCount() % SAMPLE_BUNCH;
        size_t last = signal->getSamplesCount() - remaining - SAMPLE_BUNCH;

        // set the start derivative
        double derivative[] = {0, (signal->sample(1) - signal->sample(0)) / normalization};
        double secDerivative[] = {0, (signal->sample(2) - signal->sample(1)) / normalization - derivative[1]};

        // iterate over all samples
        for (size_t i = 0; i < last; i += SAMPLE_BUNCH) {

          // get start and end.
          size_t start = i;
          size_t end = i + SAMPLE_BUNCH;

          // first of estimate the derivatives and shift
          // one forward.
          derivative[0] = derivative[1];
          secDerivative[0] = secDerivative[1];
          derivative[1] = (signal->sample(end) - signal->sample(end - 2)) / (2 * normalization);
          secDerivative[1] = (signal->sample(end + 1) - 2 * signal->sample(end) - 2 * signal->sample(end - 2)
              - signal->sample(end - 3)) / (2 * normalization);

          // fill samples
          fillSamples(start, end, derivative, secDerivative, widthBetween, signal, &result);
        }

        // get start and end.
        size_t first = last;
        last = first + remaining;

        // first of estimate the derivatives and shift
        // one forward.
        derivative[0] = derivative[1];
        secDerivative[0] = secDerivative[1];
        derivative[1] = (signal->sample(last - 1) - signal->sample(last - 2)) / normalization;
        secDerivative[1] = derivative[1] - (signal->sample(last - 2) - signal->sample(last - 3)) / normalization;

        // fill samples
        fillSamples(first, last, derivative, secDerivative, widthBetween, signal, &result);
      }

    Aquila::SignalSource* approxInvSignal = new Aquila::SignalSource(result, signal->getSampleFrequency());
    return approxInvSignal;
  }

  void fillSamples(size_t start, size_t end, double* derivative, double* secDerivative, double widthBetween, const Aquila::SignalSource *signal, std::vector<double>* result) {

    // gain best alpha
    vec::fixed<POLYNOM_DEGREE+1> alpha;
    alpha = optimalAlpha(start, end, widthBetween, derivative, secDerivative, signal, alpha);

    // fill in the values
    for (size_t k = start; k < end; k++) {
      double x = widthBetween * k;
      double c = 1;
      double y = 0;
      for (int l = 0; l < POLYNOM_DEGREE; l++) {
        y -= c * alpha(l);
        c *= x;
      }
      (*result)[k] = y;
    }
  }

  colvec &optimalAlpha(const size_t start, const size_t end, double sampleDistance,
                       double* derivative, double* secDerivative,
                       const Aquila::SignalSource *signal, colvec &out) {

    // calculate distance
    const size_t distance = end - start;

    // create fixed t
    colvec::fixed<6> t;

    // place start values
    t[0] = signal->sample(start);
    t[1] = signal->sample(end - 1);

    // place derivatives
    t[2] = derivative[0];
    t[3] = derivative[1];

    // place secondDerivatives
    t[4] = secDerivative[0];
    t[5] = secDerivative[1];

    // generate P
    mat::fixed<6, POLYNOM_DEGREE + 1> P;
    P = fillWithPolynomial(0, sampleDistance * start, P);
    P = fillWithPolynomial(1, sampleDistance * (end - 1), P);
    P = fillWithDerivative(2, sampleDistance * start, P);
    P = fillWithDerivative(3, sampleDistance * (end - 1), P);
    P = fillWithSecDerivative(4, sampleDistance * start, P);
    P = fillWithSecDerivative(5, sampleDistance * (end - 1), P);

    // calculate pseudo inverse
    out = pinv(P) * t;
    return out;
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

    // create first field
    matrix(row,0) = 0;
    int cLeft = 1;
    double cRight = 1;

    // create rest
    for (int i = 1; i < POLYNOM_DEGREE; i++) {
      matrix(row,i) = cLeft * cRight;
      cLeft++;
      cRight *= x;
    }

    return matrix;
  }

  mat& fillWithSecDerivative(int row, double x, mat &matrix) {

    // set two zero values
    matrix(row,0) = 0;
    matrix(row,1) = 0;

    // counter for x
    double cRight = 1;
    int cLeft = 2;

    // create rest
    for (int i = 1; i < POLYNOM_DEGREE; i++) {
      matrix(row,i) = cLeft * (cLeft - 1) * cRight;
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