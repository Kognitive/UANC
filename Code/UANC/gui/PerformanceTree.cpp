//
// Created by daniel on 26.01.17.
//


#include "PerformanceTree.h"

namespace uanc {
namespace gui {

PerformanceTree::PerformanceTree(std::shared_ptr<PlotWidget> parent) {
  // save reference to parent widget
  _parent = parent;
}

void SignalPlot::setData(QCPDataMap *data, bool copy) {
  graph(0)->setData(data, copy);
  graph(0)->rescaleAxes();
}
}
}
