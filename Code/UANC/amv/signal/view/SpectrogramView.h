/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SPECTROGRAMIEW_H
#define UANC_SPECTROGRAMIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>

namespace uanc {
namespace amv {
namespace signal {
namespace view {

// TODO Vladi Implement spektrogram view.

class SpectrogramView : public uanc::amv::AlgorithmView<model::SpectrogramModel> {

 public:

  QWidget *produceWidget() final;

  void setData(model::SpectrogramModel *data) final;

};

}
}
}
}

#endif //UANC_SPECTROGRAMIEW_H
