//
// Created by markus on 16.01.17.
//

#ifndef UANC_ANCMODEL_H
#define UANC_ANCMODEL_H

#include <Code/UANC/amv/SignalModel.h>
#include <memory>

namespace uanc { namespace amv { namespace anc { namespace model {

class ANCModel : public uanc::amv::SignalModel {
 public:
  std::shared_ptr<Aquila::SignalSource> inverted;
};

}}}}
#endif //UANC_ANCMODEL_H
