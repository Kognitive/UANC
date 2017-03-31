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

#ifndef CODE_UANC_GUI_MAINWIDGET_H_
#define CODE_UANC_GUI_MAINWIDGET_H_

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <map>
#include <memory>
#include <vector>
#include "Code/libs/qprogressindicator/QProgressIndicator.h"
#include "Code/UANC/amv/Algorithm.h"
#include "Code/UANC/amv/AlgorithmThread.h"
#include "Code/UANC/amv/anc/algorithm/InverseDirectAlgorithm.h"
#include "Code/UANC/util/SignalManager.h"
#include "PlotWidget.h"

namespace uanc {
namespace gui {

class MainWidget : public QWidget {
Q_OBJECT

 public:
  /** \brief This is the main widget constructor.
   *
   * This basically initializes the gui and does some other
   * initialization stuff.
   */
  MainWidget();

  /** \brief loads the signal source.
   *
   * This method loads a signal source in the top tab view.
   * @param signalSource the signal source to load.
   */
  void loadSignalSource(std::shared_ptr<InvertedModel> signalSource);

 private:
  /** This represents a mapping between the views and
  std::map<int, std::shared_ptr<std::vector<std::shared_ptr<QWidget>>>> _waveViewMapping;

  This represents a map between the waves and the algorithms . */
  std::map<int,
           std::shared_ptr<
               std::vector<
                   std::shared_ptr<
                       uanc::amv::IAlgorithm>>>> _waveAlgorithMapping;

  /** \brief Holds the apply button
   *
   * This basically holds the left button in the middle
   */
  QPushButton* _buttonApply;

  /** \brief Hold the bottom plot
   *
   * This basically holds the right button in the middle
   */
  QComboBox* _cmbAlgorithm;

  /** Represents a tab widget displayed in the top region. */
  QTabWidget* _tabWidget;

  /** Represents a detailed tab widget. */
  QTabWidget* _detailTabWidget;

  /** Holds the progress indicator. */
  QProgressIndicator* _progressIndicator;

  /** Holds the algorithm Thread. */
  AlgorithmThread* algoThread = nullptr;
  /** Holds the algorithm */
  IAlgorithm* _algorithm = nullptr;
  /** Holds the tab index of the algorithm. */
  int _algorithmTabIndex = 0;

  /** \brief Maps gets used to save algorithms
   *
   * Basically create a vector which can hold references to the appropriate algorithms
   */
  std::shared_ptr<std::vector<uanc::amv::IAlgorithm *>> _algorithmList;

  /** \brief This method will setup the gui appropriately
   *
   * It creates basically a main widget and a menu inside of the main window.
   */
  void setupGUI();

  /** \brief This method gets used to show the algorithms inside of the combobox
   *
   * This method displays the algorithms inside of the combobox.
   */
  void showAvailableAlgorithms();

  /** \brief This method can be used to apply an algorithm to the inner data.
   *
   * This algorithm basically applies the algorithm to the inner data.
   *
   * @param algorithm The algorithm to use
   */
  int applyAlgorithm(uanc::amv::IAlgorithm *algorithm); public slots:

  /** Gets called when the algorithm is finished. */
  void algorithmFinished();

  /** \brief This gets fired, when the apply button is clicked
   *
   * Gets fired, whenever a user clicks on the apply button.
   */
  void applyClicked();

  /** \brief Simple signal for a differenct selected tab */
  void tabSelected();

  // Definition for the tab control at the top as well as the bottom.

  /** \brief This gets fired, when a wave tab is closed
 *
 * This gets fired, when a wave tab is closed.
 */
  void waveClosed(const int &index);

  /** \brief This gets fired, when a algorithm tab is closed
*
* This gets fired, when a algorithm tab is closed.
*/
  void algorithmClosed(const int &index);
};

}  // namespace gui
}  // namespace uanc

#endif  // CODE_UANC_GUI_MAINWIDGET_H_
