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

#ifndef UANC_CONTROL_H
#define UANC_CONTROL_H

#include <Code/libs/qplot/qcustomplot.h>
#include <memory>
#include "PlotWidget.h"

namespace uanc {
namespace gui {

class PlotWidget;

class Control : public QCustomPlot {

 Q_OBJECT

 public:
  /** \brief Constructor of Control class
   *
   * @param parent this is the parent widget
   */
  Control(PlotWidget* parent);

/** \brief rescales the axes for the data
     *         rescales the axis to a given minimum and maximum of a data
     * @param *data this is the data that has to be rescaled
     * @param maxDataValue this is the maximum value in the data
     * @param minDataValue this is the minimum value in the data
     */
  void setData(QCPGraphDataContainer *data, double maxDataValue, double minDataValue);

   /** \brief updates navigation box
   *         updates navigation box after zoom
   * @param signalZoomRange the range of the zoomed signal
   */
  void updateNavBox(QCPRange signalZoomRange);

  /**
   * retrieve the left box
   */
  double getBoxLeft();
  /**
   * retrieve the right box
   */
  double getBoxRight();

 private slots:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *e) override;

 private:
  PlotWidget* _parent;

  /** \brief Holds the colors for the plots
   *
   * Holds the QColors for the plots.
   */
  QColor _graphColor, _boxColor, _boxBoarderColor;

  QCPItemRect* _navigationBox;

  /**
   * \brief Holds the maximum and minimum amplitude of the current signal
   *
   * Holds the maximum and minimum amplitude of the current signal.
   */
  double _minSignalAmplitude, _maxSignalAmplitude;

  int _pressedX = -1;
  double _mousePressBoxPosLeft = -1.0, _mousePressBoxPosRight = -1.0;
  bool _pressedOnNavBox = false;

  bool cursorOnNavBox(QMouseEvent *event);

  /**
 * \brief Holds the maximum value of the x-axis
 *
 * Holds the maximum value on the x-axis
 */
  double _maxRangeXAxis;
};

}
}

#endif //UANC_CONTROL_H
