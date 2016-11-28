/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_MAINWIDGET_H
#define UANC_MAINWIDGET_H

#include <QtWidgets/QWidget>
#include <memory>
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/libs/qplot/qcustomplot.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "Code/UANC/algorithm/Algorithm.h"
#include "Code/UANC/algorithm/InverseDirectAlgorithm.h"
#include "Code/UANC/algorithm/InverseFFTAlgorithm.h"

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

  /** \brief Basically places an input signal inside of the widget.
   *
   * This sets an input signal inside of the widget
   * @param signalSource the signal source to set
   */
  void setSignalInputSource(std::shared_ptr<Aquila::SignalSource> signalSource);

  /** \brief Gets the output signal of the widget.
   *
   * This method gets the output signal of the method.
   * @return The signal source of the output
   */
  std::shared_ptr<Aquila::SignalSource> getSignalOutputSource();

 private:

  /** \brief Holds the top plot
   *
   * This basically holds the top plot
   */
  std::unique_ptr<QCustomPlot> _plotTop;

  /** \brief Hold the bottom plot
   *
   * This basically holds the bottom plot
   */
  std::unique_ptr<QCustomPlot> _plotBottom;

  /** \brief Holds the apply button
   *
   * This basically holds the left button in the middle
   */
  std::unique_ptr<QPushButton> _buttonApply;

  /** \brief Hold the bottom plot
   *
   * This basically holds the right button in the middle
   */
  std::unique_ptr<QComboBox> _cmbAlgorithm;

  /** \brief Maps gets used to save algorithms
   *
   * Basically create a vector which can hold references to the appropriate algorithms
   */
  std::vector<uanc::algorithm::Algorithm*> _algorithmList;

  /** \brief This enum contains the available plot positions
   *
   * Holds the available plot position. Basically top and bottom.
   */
  enum PlotPosition { TOP, BOTTOM };

  /** \brief This method will setup the gui appropriately
   *
   * It creates basically a main widget and a menu inside of the main window.
   */
  void setupGUI();

  /** \brief This method can be used to register the algorithms inside of the gui
   *
   * This method gets used to register the available algorithms.
   */
  void registerAlgorithms();

  /** \brief This method gets used to show the algorithms inside of the combobox
   *
   * This method displays the algorithms inside of the combobox.
   */
  void showAvailableAlgorithms();

  /** \brief This method should simply plot the signal to the top or bottom plot
   *
   * This should plot the signal to the top and bottom plot
   *
   * @param signal The signal which should be used during this
   * @param position The position of the plot. e.g. Top or bottom.
   */
  void plotSignal(std::shared_ptr<Aquila::SignalSource> signal, PlotPosition position);

  /** \brief This holds the signalSource field from the input
   *
   * Simply holds the signal source field which was set per setInputSignal
   */
  std::shared_ptr<Aquila::SignalSource> _signalInputSource;

  /** \brief This holds the signal source field for the processed algorithm.
   *
   * This holds the signalsource of the output
   */
  std::shared_ptr<Aquila::SignalSource> _signalOutputSource;

  /** \brief This method can be used to apply an algorithm to the inner data.
   *
   * This algorithm basically applies the algorithm to the inner data.
   *
   * @param algorithm The algorithm to use
   */
  void applyAlgorithm(algorithm::Algorithm& algorithm);

 private slots:

  /** \brief This gets fired, when the apply button is clicked
   *
   * Gets fired, whenever a user clicks on the apply button.
   */
  void applyClicked();
};

}
}
#endif //UANC_MAINWIDGET_H
