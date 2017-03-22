//
// Created by jannewulf on 12.12.16.
//

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

    // if box is in range of graph, then replot, else abort
    if (left < 0 || right > _parent->lastIndex())
      return;
    updateNavBox(QCPRange(left, right));
    _parent->controlChanged();
  } else if (cursorOnNavBox(event)) {
    setCursor(Qt::CursorShape::OpenHandCursor);
  } else {
    unsetCursor();
  }
}

bool Control::cursorOnNavBox(QMouseEvent *event) {
  double coordX = xAxis->pixelToCoord(event->x());
  return getBoxLeft() <= coordX && coordX <= getBoxRight();
}

}
}
