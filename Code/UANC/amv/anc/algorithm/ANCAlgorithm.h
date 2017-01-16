//
// Created by markus on 16.01.17.
//

#ifndef UANC_ANCALGORITHM_H
#define UANC_ANCALGORITHM_H

#include <Code/UANC/amv/Algorithm.h>

namespace uanc { namespace amv { namespace anc { namespace algorithm {

template<class viewmodel, class datamodel>
class ANCAlgorithm : public uanc::amv::Algorithm<viewmodel> {

 protected:
  viewmodel* execute(uanc::amv::SignalModel* input) final {
    this->model = this->createEmptyModel();
    this->invert(input);
    return this->getModel();
  }

  datamodel* getModel() {
    return this->model;
  }

  virtual viewmodel* createEmptyModel() = 0;

  virtual void invert(uanc::amv::SignalModel* input) = 0;

 private:
  datamodel* model;
};

template<class datamodel>
class ANCAlgorithm : public ANCAlgorithm<datamodel, datamodel> {};

}}}}

#endif //UANC_ANCALGORITHM_H
