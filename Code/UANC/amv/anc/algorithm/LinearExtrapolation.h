//
// Created by janne on 12.03.17.
//

#ifndef UANC_LINEAREXTRAPOLATION_H
#define UANC_LINEAREXTRAPOLATION_H

namespace uanc {
namespace amv {
namespace anc {
namespace algorithm {

using namespace uanc::amv::anc;
using namespace uanc::util;

class LinearExtrapolation : public ANCAlgorithm<model::ANCModel> {
 public:

  /** \brief Returns the name of the algorithm.
   *
   * Simply passes back the name of the algorithm.
   *
   * @return Name of the algorithm
   */
  std::string getName() final { return "Lineare Extrapolation"; };

  /** \brief Inverts the input signal.
   *
   * This is actually the heart of an ANC algorithm inside of this application. It takes
   * an input model and processes it. Besides it should save its data inside the model
   * using getModel().
   *
   * @param input The input model containing the original signal.
   */
  void invert(std::shared_ptr<InvertedModel> in) final {

      std::shared_ptr <PerformanceMeasure<>> measurement(new PerformanceMeasure<>());

      // Start measurement for the inversion
      measurement->start(this->getName());
      measurement->startSubMeasure("Transformation & Inversion Left");

      // creates a new shared pointer containing the inverted signal
      auto invertedApproximated = approximate(in->left_channel.get());

      // Invertation is done. Stop mesurement
      measurement->stopSubMeasure();

      std::shared_ptr <Aquila::SignalSource> out(invertedApproximated);

      this->getModel()->left_channel = in->left_channel;

      // ------------------------------- RIGHT CHANNEL ----------------------------------

      measurement->startSubMeasure("Transformation & Inversion Right");

      // creates a new shared pointer containing the inverted signal
      auto invertedApproximatedr = approximate(in->right_channel.get());

      // Invertation is done. Stop mesurement
      measurement->stopSubMeasure();
      measurement->stop();
      this->getModel()->defaultRegister.registerCustomMeasurement(measurement);

      std::shared_ptr <Aquila::SignalSource> outr(invertedApproximated);

      this->getModel()->right_channel = in->right_channel;
      this->getModel()->inverted = std::shared_ptr<InvertedModel>(new InvertedModel);
      this->getModel()->inverted->left_channel = out;
      this->getModel()->inverted->right_channel = outr;
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
      return new LinearExtrapolation();
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
  /**
   * This field saves the amount of samples that will be approximated.
   * A factor of 1 is equal to Inverse Direct Algorithm.
   */
  int _extrapolationFactor = 15;

  /** \brief This function computes a approximated inverted signal of the input signal.
   *
   * @param signal The input signal which will be approximated and inverted.
   * @return A new signal which is approximated and inverted.
   */
  Aquila::SignalSource* approximate(Aquila::SignalSource* signal) {
      std::vector<double> approxInvSamples(signal->getSamplesCount());

      double slope;
      for (int i = 0; i < signal->getSamplesCount(); ++i) {
          if (i % _extrapolationFactor == 0) {
              slope = (i == signal->getSamplesCount() - 1) ? 0.0 : signal->sample(i + 1) - signal->sample(i);
              approxInvSamples[i] = - signal->sample(i);
          }
          else {
              approxInvSamples[i] = - (signal->sample(i - 1) + slope);
          }
      }

      Aquila::SignalSource* approxInvSignal = new Aquila::SignalSource(approxInvSamples, signal->getSampleFrequency());

      return approxInvSignal;
  }

};
}
}
}
}


#endif //UANC_LINEAREXTRAPOLATION_H
