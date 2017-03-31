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

#include "SignalPlot.h"

namespace uanc {
namespace gui {

SignalPlot::SignalPlot(PlotWidget *parent) {
  // save reference to parent widget
  _parent = parent;

  // set color of graph
  _graphColor = QColor(26, 107, 179);

  // add graph and set it's pen
  addGraph();
  graph(_SIGNAL)->setPen(_graphColor);

  // add error graph and hide it
  addGraph();
  graph(_ERROR)->setVisible(false);
  graph(_ERROR)->setPen(QPen(QColor("red")));

  // create lines for the plot for dragged zoom
  _zoomLineOrigin = new QCPItemStraightLine(this);
  _zoomLineTarget = new QCPItemStraightLine(this);
  _zoomLineOrigin->setVisible(false);
  _zoomLineTarget->setVisible(false);
  _zoomLineOrigin->setPen(QPen(Qt::black, 1, Qt::DotLine));
  _zoomLineTarget->setPen(QPen(Qt::black, 1, Qt::DotLine));
}

void SignalPlot::setData(QCPGraphDataContainer *data) {
  graph(_SIGNAL)->setData(QSharedPointer<QCPGraphDataContainer>(data));
  graph(_SIGNAL)->rescaleAxes();
  setExtremeValues();
}

void SignalPlot::setError(QCPGraphDataContainer *error) {
  graph(_ERROR)->setData(QSharedPointer<QCPGraphDataContainer>(error));
}

void SignalPlot::mousePressEvent(QMouseEvent *event) {
  QCustomPlot::mousePressEvent(event);
  _pressedX = event->x();
  _pressedY = event->y();
}

void SignalPlot::mouseMoveEvent(QMouseEvent *event) {
  QCustomPlot::mouseMoveEvent(event);
  if (_pressedX != -1 || _pressedY != -1) {
    setZoomLinePos(_zoomLineOrigin, xAxis->pixelToCoord(_pressedX));
    setZoomLinePos(_zoomLineTarget, xAxis->pixelToCoord(event->x()));
    _zoomLineOrigin->setVisible(true);
    _zoomLineTarget->setVisible(true);
    replot();
  }
}

void SignalPlot::mouseReleaseEvent(QMouseEvent *event) {
  QCustomPlot::mouseReleaseEvent(event);
  if (_pressedX == event->x() && _pressedY == event->y()) {
    // clicked
    if (event->button() == Qt::LeftButton)
      zoom(xAxis->pixelToCoord(event->x()));
    else if (event->button() == Qt::RightButton)
      unzoom(xAxis->pixelToCoord(event->x()));
  } else {
    // dragged
    if (event->button() == Qt::LeftButton)
      zoomRange(xAxis->pixelToCoord(_pressedX), xAxis->pixelToCoord(event->x()));
  }

  // reset pressed coordinates
  _pressedX = -1;
  _pressedY = -1;

  // set zoom lines to invisible again
  _zoomLineOrigin->setVisible(false);
  _zoomLineTarget->setVisible(false);

  // update both plots
  rescaleYAxis();
  replot();
  _parent->plotChanged();
}

void SignalPlot::zoom(double center) {
  xAxis->setRange(scaleRange(1.0 / _ZOOMFACTOR, center));
  rescaleYAxis();

}

void SignalPlot::unzoom(double center) {
  xAxis->setRange(scaleRange(_ZOOMFACTOR, center));
  rescaleYAxis();
}

void SignalPlot::zoomRange(double press, double release) {
  double lower = std::min(press, release);
  double upper = std::max(press, release);
  xAxis->setRange(std::max(lower, 0.0), std::min(upper, _parent->lastIndex()));
}

QCPRange SignalPlot::scaleRange(double factor, double center) {
  QCPRange oldRange = xAxis->range();
  QCPRange newRange;
  newRange.lower = std::max((oldRange.lower - center) * factor + center, 0.0);
  newRange.upper = std::min((oldRange.upper - center) * factor + center, _parent->lastIndex());
  if (QCPRange::validRange(newRange))
    newRange = newRange.sanitizedForLinScale();
  return newRange;
}

void SignalPlot::setRange(double lower, double upper) {
  xAxis->setRange(lower, upper);
  rescaleYAxis();
  replot();
}

void SignalPlot::setZoomLinePos(QCPItemStraightLine *zoomLine, double xCoord) {
  zoomLine->point1->setCoords(xCoord, 0);
  zoomLine->point2->setCoords(xCoord, 1);
}

void SignalPlot::hideError(bool hide) {
  graph(_ERROR)->setVisible(hide);
  replot();
}

void SignalPlot::setExtremeValues() {
  _MapExtremeValues = std::shared_ptr<QCPGraphDataContainer>(new QCPGraphDataContainer);
  auto data = graph(_SIGNAL)->data();

  QCPGraphData newDatapoint;
  // get all extreme values (via state machine)
  int state = 0;
  for (auto i = 1; i < data->size(); ++i) {
    switch (state) {
      case 0 : {
        // canidate for new maximum
        if (data->at(i)->value > data->at(i - 1)->value) state = 1;
        // canidate for new minimum
        if (data->at(i)->value < data->at(i - 1)->value) state = 2;
        break;
      }
      case 1 : {
        // found new maximum
        if (data->at(i)->value < data->at(i-1)->value) {
          newDatapoint.key = data->at(i)->key;
          newDatapoint.value = data->at(i)->value;
          _MapExtremeValues->add(newDatapoint);
          state = 0;
        }
        break;
      }
      case 2 : {
        // found new minimum
        if (data->at(i)->value > data->at(i-1)->value) {
          newDatapoint.key = data->at(i)->key;
          newDatapoint.value = data->at(i)->value;
          _MapExtremeValues->add(newDatapoint);
          state = 0;
        }
        break;
      }
    }
  }
}

void SignalPlot::rescaleYAxis() {

  auto &data = _MapExtremeValues;

  double lower = xAxis->range().lower;
  double upper = xAxis->range().upper;

  double dHigh = std::numeric_limits<double>::min();
  double dLow = std::numeric_limits<double>::max();

  auto it = data->findBegin(lower);
  while (it != data->findEnd(upper)) {
    if (it->value > dHigh) dHigh = it->value;
    if (it->value < dLow) dLow = it->value;
    it++;
  }

  if(_centeredYAxis) {
    if(dHigh > (dLow * -1)){
      yAxis->setRange((dHigh * -1), dHigh);
    } else {
      yAxis->setRange(dLow, (dLow * -1));
    }

  } else {
    yAxis->setRange(0, dHigh);
  }


}
}
}
