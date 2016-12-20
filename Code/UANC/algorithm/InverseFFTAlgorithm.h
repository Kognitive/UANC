//
// Created by markus on 11/25/16.
//

#ifndef UANC_INVERSEFFTALGORITHM_H
#define UANC_INVERSEFFTALGORITHM_H

#include "Algorithm.h"
#include <Code/UANC/gui/model/FFTModel.h>
#include <Code/UANC/gui/views/FFTView.h>

namespace uanc {
    namespace algorithm {

        class InverseFFTAlgorithm : public Algorithm {
        public:

            /** \brief This should be implemented by the subclasses.
             *
             * It should pass back an appropriate Name for this algorithm
             *
             * @return the name of this algorithm.
             *
             */
            std::string getName() override {
                return "Inverse FFT";
            }

            /** \brief Represents the execution of the inverse fft algorithm.
             *
             * This method should take a vector of size n from the type SignalSource and outputs
             * a vector of size n, also of type SignalSource. Note that the output should be the inverted
             * signal using fft inverse algorithm
             *
             * @return the processed vector itself.
             */
            std::shared_ptr<Aquila::SignalSource> execute(std::shared_ptr<Aquila::SignalSource> in) override {
                return in;
            }


            /** \brief Can be used to clone the algorithm.
           *
           * This can be used to clone the algorithm
           * @return The cloned algorithm
           */
            Algorithm *clone() override {
                new InverseFFTAlgorithm();
            }

        protected:
            uanc::gui::model::AlgorithmModel *constructModel() override {
                auto model = new uanc::gui::model::FFTModel();
                return model;
            }


            uanc::gui::views::AlgorithmView *constructView() override {
                auto view = new uanc::gui::views::FFTView();
                return view;
            }
        };

    }
}
#endif //UANC_INVERSEFFTALGORITHM_H
