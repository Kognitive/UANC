//
// Created by daniel on 28.01.17.
//

#include <QtWidgets/QTreeWidget>
#include "PMWidget.h"

namespace uanc {
namespace gui {

PMWidget::PMWidget() {
  this->initialize();
}

void PMWidget::initialize() {
  // create an empty tree view

}

void PMWidget::setData(std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>> *performanceData) {
  // save pointer to performance information in member
  _data = performanceData;

  // create tree view and set data
  QTreeWidget *treeWidget = new QTreeWidget;
  treeWidget->setColumnCount(2);

  // Fill tree view
  for (std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>>::iterator it = _data->begin();
       it != _data->end(); ++it){
    auto measurement = it->shared_ptr()->getRootMeasure();
    // add new tree root item
    QTreeWidgetItem *qItem = new QTreeWidgetItem(treeWidget);
    // set measurment title in first column
    qItem->setText(0, QString::fromStdString(measurement->measureTitle));
    // set duration time in second column
    auto msTime = std::chrono::duration_cast<std::chrono::milliseconds>(measurement->getNodeDuration());
    qItem->setText(1, QString::fromStdString(std::to_string(msTime.count())));

    measurement->subsequentMeasure->
  }
}
}
}