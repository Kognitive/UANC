//
// Created by markus on 12/12/16.
//

#ifndef UANC_ALGORITHMMODEL_H
#define UANC_ALGORITHMMODEL_H

#include <Code/libs/aquila/source/SignalSource.h>

namespace uanc { namespace gui { namespace model {

class AlgorithmModel {

 public:
  std::shared_ptr<Aquila::SignalSource> samples;

};

}}}

#endif //UANC_ALGORITHMMODEL_H
