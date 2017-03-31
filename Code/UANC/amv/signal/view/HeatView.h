/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
