//
// Created by daniel on 26.01.17.
//

#ifndef UANC_PERFORMANCETREE_H
#define UANC_PERFORMANCETREE_H


#include <memory>
#include <Code/libs/qplot/qcustomplot.h>

#include "PlotWidget.h"

namespace uanc {
namespace gui {

class PlotWidget;

class PerformanceTree : public QTreeView {

 Q_OBJECT

 public:
  PerformanceTree(std::shared_ptr<PlotWidget> parent);

  void setData(QCPDataMap *data, bool copy = false);

 private slots:

 private:
  /** \brief Holds reference to the parent widget
   *
   */
  std::shared_ptr<PlotWidget> _parent;

};

}
}
#endif //UANC_PERFORMANCETREE_H
