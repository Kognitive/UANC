//
// Created by markus on 24.03.17.
//

#ifndef UANC_ALGORITHMTHREAD_H
#define UANC_ALGORITHMTHREAD_H

#include <QThread>
#include "IAlgorithm.h"

namespace uanc {
  namespace amv {

    class AlgorithmThread : public QThread {
      Q_OBJECT

     public slots:

      /** \brief Can be used to set an algorithm.
       *
       * This method takes a pointer and saves it internally, to actually know
       * which algorithm to use for the operation.
       *
       * @param algorithm The Algorithm to use.
       * @param model The Model to invert.
       */
      void setAlgorithm(IAlgorithm* algorithm, std::shared_ptr<InvertedModel> model) {
        this->_algorithm = algorithm;
        this->_model = model;
      }

     private:

      /** Holds a pointer to the algorithm. */
      IAlgorithm* _algorithm = nullptr;
      std::shared_ptr<InvertedModel> _model;

     protected:

        /** \brief Ru method of this thread.
         *
         * This method does the running of the algorithm.
         */
        void run() final {
          _algorithm->process(_model);
          emit algorithmFinished();
        }

      signals:

        /** Gets called when the algorithm is finished. */
        void algorithmFinished();
    };
  }
}

#endif //UANC_ALGORITHMTHREAD_H
