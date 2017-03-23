/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_HEATVIEW_H
#define UANC_HEATVIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/gui/HeatWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/libs/aquila/functions.h>

namespace uanc {
namespace amv {
namespace signal {
namespace view {

using namespace uanc::gui;

class HeatView : public uanc::amv::AlgorithmView<model::SpectrogramModel> {

 public:

  QWidget *produceWidget() final {
    _heatWidget = new HeatWidget();
    return _heatWidget;
  }

  void setData(std::shared_ptr<model::SpectrogramModel> data) final {
    _heatWidget->setData(data);
  }

 private:
 HeatWidget* _heatWidget;
};

}
}
}
}

#endif //UANC_HEATVIEW_H
