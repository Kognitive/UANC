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

#ifndef UANC_PMWIDGET_H
#define UANC_PMWIDGET_H

#include <Code/libs/aquila/source/SignalSource.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QPushButton>
#include <memory>
#include <Code/UANC/util/PerformanceMeasure.h>

namespace uanc {
namespace gui {

class PMWidget : public QWidget {
  Q_OBJECT
 public:
  /**
   * Contructor
   */
  PMWidget();

  /** \brief This method is for setting the measurement information.
   * This method is for setting the measurement information.
   *
   * @param signal The \ref Aquila::SignalSource which will be plotted
   */
  void setData(std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>> performanceData);

 private:
  /**
   * \brief Holds the plotted signal.
   */
  std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>> _data;

  QTreeWidget* treeWidget;
  QPushButton* btnShowPerformance;

  /**
   * \brief This method initializes the plots.
   */
  void initialize();

  /**
 * \brief This method adds a new child to a parrent
 * @parm parent The \ref QTreeWidgetItem
   *     measurement The \ref util::PerformanceMeasure<>
 */
  void addTreeChild(QTreeWidgetItem *parent,
                    std::vector<std::shared_ptr<uanc::util::PerformanceMeasureNode<>>> *measurements);

  /** Holds state if performance is shown. */
  bool performanceShown = false;

 public slots:
    /** \brief simple hides or shows the performance measurement
     *
     */
  void tooglePerformance();
};

}
}
#endif //UANC_PMWIDGET_H
