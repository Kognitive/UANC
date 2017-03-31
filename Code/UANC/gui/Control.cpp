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

#include <iostream>
#include "Control.h"

namespace uanc {
namespace gui {

Control::Control(PlotWidget* parent) {
  // save reference to parent widget
  _parent = parent;

  // set colors
  _graphColor = QColor(32, 127, 212); //QColor(26, 140, 255);
  _boxBoarderColor = QColor(0, 61, 102);
  _boxColor = QColor(20, 20, 20, 40);

  // create graph
  addGraph();
  graph()->setPen(QPen(_graphColor));

  // hide axes and grids
  axisRect()->setAutoMargins(QCP::msNone);
  axisRect()->setMargins(QMargins(1, 0, 0, 1));
  this->xAxis->setVisible(false);
  this->yAxis->setVisible(false);

  // create navigation box
  _navigationBox = new QCPItemRect(this);
  _navigationBox->setPen(QPen(_boxBoarderColor));
  _navigationBox->setBrush(_boxColor);
  _maxSignalAmplitude = 5.0;
  _minSignalAmplitude = 0.0;
  updateNavBox(QCPRange(0.0, 1.0));
}

void Control::updateNavBox(QCPRange signalZoomRange) {
  // set position and size of navigation box
  double minX = signalZoomRange.lower;
  double maxX = signalZoomRange.upper;
  _navigationBox->topLeft->setCoords(minX, _maxSignalAmplitude + 10);
  _navigationBox->bottomRight->setCoords(maxX, _minSignalAmplitude - 10);
  replot();
}

void Control::setData(QCPGraphDataContainer *data, double maxDataValue, double minDataValue) {
  graph()->setData(QSharedPointer<QCPGraphDataContainer>(data));
  graph()->rescaleAxes();
  _maxSignalAmplitude = maxDataValue;
  _minSignalAmplitude = minDataValue;
  _maxRangeXAxis = _parent->getPlotXRange().upper;
  updateNavBox(_parent->getPlotXRange());
}

double Control::getBoxLeft() {
  return _navigationBox->topLeft->coords().x();
}

double Control::getBoxRight() {
  return _navigationBox->bottomRight->coords().x();
}

void Control::mousePressEvent(QMouseEvent *event) {
  QCustomPlot::mousePressEvent(event);
  _pressedX = event->x();
  _mousePressBoxPosLeft = getBoxLeft();
  _mousePressBoxPosRight = getBoxRight();

  if (cursorOnNavBox(event))
    _pressedOnNavBox = true;
}

void Control::mouseDoubleClickEvent(QMouseEvent *e)
{
  if ( e->button() == Qt::LeftButton )
  {
    _pressedOnNavBox= false;
    if (cursorOnNavBox(e)) {
      updateNavBox(QCPRange(0.0, _maxRangeXAxis));
      _parent->controlChanged();
    }
  }
}

void Control::mouseReleaseEvent(QMouseEvent *event) {
  QCustomPlot::mouseReleaseEvent(event);
  _pressedX = -1;
  _pressedOnNavBox = false;

  if (cursorOnNavBox(event))
    setCursor(Qt::CursorShape::OpenHandCursor);
  else
    unsetCursor();
}

void Control::mouseMoveEvent(QMouseEvent *event) {
  QCustomPlot::mouseMoveEvent(event);
  if (_pressedOnNavBox) {
    setCursor(Qt::CursorShape::ClosedHandCursor);
    double shift = xAxis->pixelToCoord(event->x() - _pressedX);
    double left = _mousePressBoxPosLeft + shift;
    double right = _mousePressBoxPosRight + shift;

    // if box is in range of graph, then replot, else set box und min/max pos
    if (left < 0 || right > _parent->lastIndex()) {
      double r = right-left;
      if(left < 0)
        updateNavBox(QCPRange(0.0, r));
      if(right > _parent->lastIndex())
        updateNavBox(QCPRange(_parent->lastIndex() -r, _parent->lastIndex()));
      _parent->controlChanged();
      return;
    }

    updateNavBox(QCPRange(left, right));
    _parent->controlChanged();
  } else if (cursorOnNavBox(event)) {
    setCursor(Qt::CursorShape::OpenHandCursor);
  } else {
    unsetCursor();
  }
}

bool Control::cursorOnNavBox(QMouseEvent *event) {
  double leftBoundary = getBoxLeft();
  double rightBoundary = getBoxRight();

  double threshold = 0.005 * _maxRangeXAxis / 2;

  // assign minimum range if under threshold
  double range = rightBoundary - leftBoundary;
  if (range < 2 * threshold) {
    double middle = leftBoundary + range / 2;
    leftBoundary = middle - threshold;
    rightBoundary = middle + threshold;
  }

  double coordX = xAxis->pixelToCoord(event->x());
  return leftBoundary <= coordX && coordX <= rightBoundary;
}

}
}
