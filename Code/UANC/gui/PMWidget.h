//
// Created by daniel on 28.01.17.
//

#ifndef UANC_PMWIDGET_H
#define UANC_PMWIDGET_H

#include <Code/libs/aquila/source/SignalSource.h>
#include <QtWidgets/QWidget>
#include <memory>
#include <Code/UANC/util/PerformanceMeasure.h>

namespace uanc {
namespace gui {

class PMWidget : public QWidget {
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
  void setData(std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>> *performanceData);

 private:
  /**
   * \brief Holds the plotted signal.
   */
  std::vector<std::shared_ptr<uanc::util::PerformanceMeasure<>>> *_data;

  /**
   * \brief This method initializes the plots.
   */
  void initialize();

  /**
   * \brief This method adds a new root item.
   * @parm measurement The \ref util::PerformanceMeasure<>
   */
  void addTreeRoot(std::shared_ptr<uanc::util::PerformanceMeasure<>> *measurement);

  /**
 * \brief This method adds a new child to a parrent
 * @parm parent The \ref QTreeWidgetItem
   *     measurement The \ref util::PerformanceMeasure<>
 */
  void addTreeChild(QTreeWidgetItem *parent,
                    std::shared_ptr<uanc::util::PerformanceMeasure<>> *measurement);
};

}
}
#endif //UANC_PMWIDGET_H
