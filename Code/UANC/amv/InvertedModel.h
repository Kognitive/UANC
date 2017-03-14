/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_INVERTEDMODEL_H
#define UANC_INVERTEDMODEL_H

#include <Code/UANC/amv/SignalModel.h>
#include <memory>
#include <Code/UANC/util/PerformanceMeasure.h>

namespace uanc {
namespace amv {

using namespace uanc::util;

/** \brief This is an InvertedModel.
 *
 * This model gets derived from the SignalModel. It adds a field containing
 * the inverted signal to the original signal in SignalModel.
 */
class InvertedModel : public uanc::amv::SignalModel {
 public:

    /** \brief Holds the inverted signal.
     *
     * This field gets used, to save the inverted signal, in addition to
     * the original signal, which is placed in the parent class SignalModel.
     */
    std::shared_ptr<SignalModel> inverted = NULL;
};

}
}
#endif //UANC_INVERTEDMODEL_H
