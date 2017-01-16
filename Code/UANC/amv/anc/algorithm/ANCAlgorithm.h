//
// Created by markus on 16.01.17.
//

#ifndef UANC_ANCALGORITHM_H
#define UANC_ANCALGORITHM_H

#include <Code/UANC/amv/Algorithm.h>

namespace uanc { namespace amv { namespace anc { namespace algorithm {

template<class outputmodel>
class ANCAlgorithm : public uanc::amv::Algorithm<outputmodel> {

 protected:
  outputmodel* execute(uanc::amv::SignalModel* input) final {
    this->model = this->createEmptyModel();
    this->invert(input);
    return this->model;
  }

  outputmodel* getModel() {
    return this->model;
  }

  virtual outputmodel* createEmptyModel() = 0;

  virtual void invert(uanc::amv::SignalModel* input) = 0;

 private:
  outputmodel* model;
};

}}}}

#endif //UANC_ANCALGORITHM_H
