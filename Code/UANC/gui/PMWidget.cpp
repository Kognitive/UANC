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

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
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

  // create new button
  btnShowPerformance = new QPushButton();
  btnShowPerformance->setText("<");
  btnShowPerformance->setFixedWidth(20);
  btnShowPerformance->setFixedHeight(50);


  // create tree view and set data
  treeWidget = new QTreeWidget;
  treeWidget->setColumnCount(2);
  treeWidget->setHeaderLabels(QStringList() << "Measurement" << "Time");

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
    auto timeString = std::to_string(msTime.count());
    qItem->setText(1, QString::fromStdString(timeString + " ms"));

    // if there are children add them
    addTreeChild(qItem, &measurement->measureSubMeasureChild);
  }

  treeWidget->expandAll();

  this->connect(btnShowPerformance, SIGNAL(pressed()), this, SLOT(tooglePerformance()));

  // set horizontal layout (splitter)
  auto layout =  new QHBoxLayout;
  layout->addWidget(btnShowPerformance);
  layout->addWidget(treeWidget);
  treeWidget->hide();

  this->setLayout(layout);
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
    auto timeString = std::to_string(msTime.count());
    qItem->setText(1, QString::fromStdString(timeString + " ms"));

    // add child to parrent
    parent->addChild(qItem);

    // if there are children add them
    addTreeChild(qItem, &it->get()->measureSubMeasureChild);
  }
}



void PMWidget::tooglePerformance() {
  if (performanceShown) {
    treeWidget->hide();
    btnShowPerformance->setText("<");
  }
  else {
    btnShowPerformance->setText(">");
    treeWidget->show();
  }

  this->performanceShown = !performanceShown;
}

}
}