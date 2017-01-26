/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <Code/UANC/gui/PlotWidget.h>
#include "SpectrogramView.h"

namespace uanc {
namespace amv {
namespace signal {
namespace view {

QWidget *SpectrogramView::produceWidget() {
  // TODO Vladi Just a testlabel
  return new QLabel("Test");
}

void SpectrogramView::setData(model::SpectrogramModel *data) {

}
}
}
}
}