//
// Created by jannewulf on 25.03.17.
//

#ifndef UANC_LOCALLYWEIGHTEDREGRESSION_H
#define UANC_LOCALLYWEIGHTEDREGRESSION_H

#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/UANC/amv/Algorithm.h>
#include <Code/UANC/amv/anc/view/PMView.h>
#include "Code/UANC/util/DummyActor.h"

#include <armadillo>
#include "ANCAlgorithm.h"

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

using namespace uanc::amv::anc;
using namespace uanc::util;
using namespace arma;

class LocallyWeightedRegression : public ANCAlgorithm<model::ANCModel> {
 public:

  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  std::string getName() final { return "Locally Weighted Regression"; };

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
    return new LocallyWeightedRegression();
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
  const double _bandwidth = 9e-1;
  const double _sigmaRidge = 1e-3;
  const int _sampleCount = 20;
  mat _weights;

  /** \brief This function computes a approximated inverted signal of the input signal.
   *
   * @param signal The input signal which will be approximated and inverted.
   * @return A new signal which is approximated and inverted.
   */
  Aquila::SignalSource *approximate(const Aquila::SignalSource *signal) {
    // precompute weights, possible because we have equally distant features
    precomputeWeights();

    // approximate new inverted signal
    std::vector<double> newSamples = std::vector<double>();
    newSamples.reserve(signal->getSamplesCount());
    for (size_t i = 0; i < signal->getSamplesCount(); i += _sampleCount) {
      // compute local linear function for restricted area
      vec theta = computeParameters(signal, i);

      // produce new approximated signal, sampled from local function
      for (size_t j = i; j < i + _sampleCount; ++j) {
        vec x = vec();
        x << 1.0 << (double) j;
        double sample = as_scalar(theta.t() * x);
        newSamples.push_back(- sample);
      }
    }

    // return inverted and approximated signal
    return new Aquila::SignalSource(newSamples, signal->getSampleFrequency());
  }

  void precomputeWeights() {
    std::vector<double> weightsList = std::vector<double>();
    weightsList.reserve((long unsigned) _sampleCount);
    for (double i = - ((double) _sampleCount) / 2.0; i < _sampleCount / 2; i += 1) {
      weightsList.push_back(computeWeight(i));
    }
    vec wVec = vec(weightsList);
    _weights = diagmat(wVec);
  }

  double computeWeight(double v) {
    double w = exp(- std::pow(distanceNorm(v), 2) / (2 * std::pow(_bandwidth, 2)));
    return w;
  }

  double distanceNorm(double v) {
    return std::abs(v);
  }

  vec computeParameters(const Aquila::SignalSource *signal, double xBegin) {
    // build x vector
    mat x = buildXmatrix(xBegin);

    // build y vector
    vec y = buildYvector(signal, x);

    // compute theta
    return inv(x.t() * _weights * x + std::pow(_sigmaRidge, 2) * eye(2,2)) * x.t() * _weights * y;
  }

  mat buildXmatrix(double xBegin) {
    mat x = linspace<vec>(xBegin, xBegin + _sampleCount - 1, (uword) _sampleCount);
    x = join_rows(x, ones((uword) _sampleCount, 1));
    return x;
  }

  vec buildYvector(const Aquila::SignalSource *signal, mat &x) {
    std::vector<double> ySTL = std::vector<double>();
    ySTL.reserve(x.n_rows);
    for (unsigned int i = 0; i < x.n_rows; ++i) {
      ySTL.push_back(signal->sample((size_t) x[i]));
    }
    vec y = vec(ySTL);
    return y;
  }
};

}
}
}
}

#endif //UANC_LOCALLYWEIGHTEDREGRESSION_H
