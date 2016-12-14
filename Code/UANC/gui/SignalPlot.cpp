//
// Created by jannewulf on 12.12.16.
//

#include "SignalPlot.h"

namespace uanc {
namespace gui {

SignalPlot::SignalPlot(std::shared_ptr<PlotWidget> parent) {
  // save reference to parent widget
  _parent = parent;

  // set color of graph
  _graphColor = QColor(43, 140, 190);

  // add graph and set it's pen
  addGraph();
  graph(0)->setPen(_graphColor);

  // create lines for the plot for dragged zoom
  _zoomLineOrigin = std::shared_ptr<QCPItemStraightLine>(new QCPItemStraightLine(this));
  _zoomLineTarget = std::shared_ptr<QCPItemStraightLine>(new QCPItemStraightLine(this));
  _zoomLineOrigin->setVisible(false);
  _zoomLineTarget->setVisible(false);
  _zoomLineOrigin->setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));
  _zoomLineTarget->setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));
  addItem(_zoomLineOrigin.get());
  addItem(_zoomLineTarget.get());
}

void SignalPlot::setData(QCPDataMap *data, bool copy) {
  graph(0)->setData(data, copy);
  graph(0)->rescaleAxes();
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
  replot();
  _parent->plotChanged();
}

void SignalPlot::zoom(double center) {
  xAxis->setRange(scaleRange(1.0 / _ZOOMFACTOR, center));
}

void SignalPlot::unzoom(double center) {
  xAxis->setRange(scaleRange(_ZOOMFACTOR, center));
}

void SignalPlot::zoomRange(double press, double release) {
  double lower = std::min(press, release);
  double upper = std::max(press, release);
  xAxis->setRange(std::max(lower, 0.0), upper);
}

QCPRange SignalPlot::scaleRange(double factor, double center) {
  QCPRange oldRange = xAxis->range();
  QCPRange newRange;
  newRange.lower = std::max((oldRange.lower-center)* factor + center, 0.0);
  newRange.upper = (oldRange.upper-center)* factor + center;
  if (QCPRange::validRange(newRange))
    newRange = newRange.sanitizedForLinScale();
  return newRange;
}

void SignalPlot::setRange(double lower, double upper) {
  xAxis->setRange(lower, upper);
  replot();
}

void SignalPlot::setZoomLinePos(std::shared_ptr<QCPItemStraightLine> zoomLine, double xCoord) {
  zoomLine->point1->setCoords(xCoord, 0);
  zoomLine->point2->setCoords(xCoord, 1);
}

}
}
