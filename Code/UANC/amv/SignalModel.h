//
// Created by markus on 12/12/16.
//

#ifndef UANC_SIGNALMODEL_H
#define UANC_SIGNALMODEL_H

#include <Code/libs/aquila/source/SignalSource.h>
#include <memory>

namespace uanc { namespace amv {

class SignalModel {

 public:
  std::shared_ptr<Aquila::SignalSource> original;
};

}}

#endif //UANC_SIGNALMODEL_H
