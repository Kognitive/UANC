//
// Created by daniel on 28.01.17.
//

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include "PMWidget.h"

namespace uanc {
namespace gui {

PMWidget::PMWidget() {
  this->initialize();
}

void PMWidget::initialize() {
  // create an empty tree view

}

void PMWidget::setData(std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>> performanceData) {
  // save pointer to performance information in member
  _data = performanceData;

  // create tree view and set data
  QTreeWidget *treeWidget = new QTreeWidget;
  treeWidget->setColumnCount(2);
  treeWidget->setHeaderLabels(QStringList() << "Measurement" << "Time in ms");

  // Fill tree view
  for (std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>>::iterator it = _data.begin();
       it != _data.end(); ++it){
    auto measurement = it->get()->getRootMeasure();
    // add new tree root item
    QTreeWidgetItem *qItem = new QTreeWidgetItem(treeWidget);
    // QTreeWidgetItem::setText(int column, const QString & text)
    // set measurment title in first column
    qItem->setText(0, QString::fromStdString(measurement->measureTitle));
    // set duration time in second column
    auto msTime = std::chrono::duration_cast<std::chrono::milliseconds>(measurement->getNodeDuration());
    qItem->setText(1, QString::fromStdString(std::to_string(msTime.count())));

    // if there are children add them
    addTreeChild(qItem, &measurement->measureSubMeasureChild);
  }
  auto vLayot = new QVBoxLayout();
  vLayot->addWidget(treeWidget);
  vLayot->totalMinimumSize();
  this->setLayout(vLayot);
}

void PMWidget::addTreeChild(QTreeWidgetItem *parent,
                            std::vector<std::shared_ptr<uanc::util::PerformanceMeasureNode<>>> *measurements) {
  for (std::vector<std::shared_ptr<uanc::util::PerformanceMeasureNode<>>>::iterator it = measurements->begin();
       it != measurements->end(); ++it){
    QTreeWidgetItem *qItem = new QTreeWidgetItem();
    // QTreeWidgetItem::setText(int column, const QString & text)
    // set measurment title in first column
    qItem->setText(0, QString::fromStdString(it->get()->measureTitle));
    // set duration time in second column
    auto msTime = std::chrono::duration_cast<std::chrono::milliseconds>(it->get()->getNodeDuration());
    qItem->setText(1, QString::fromStdString(std::to_string(msTime.count())));

    // add child to parrent
    parent->addChild(qItem);

    // if there are children add them
    addTreeChild(qItem, &it->get()->measureSubMeasureChild);
  }
}
}
}