//
// Created by jannewulf on 12.12.16.
//

#include "Control.h"

namespace uanc {
namespace gui {

Control::Control(std::shared_ptr<PlotWidget> parent) {
  // save reference to parent widget
  _parent = parent;

  // set colors
  _graphColor = QColor(166, 189, 219);
  _boxBoarderColor = QColor(166, 189, 219);
  _boxColor = QColor(166, 189, 219, 80);

  // create graph
  addGraph();
  graph()->setPen(QPen(_graphColor));

  // hide axes and grids
  axisRect()->setAutoMargins(QCP::msNone);
  axisRect()->setMargins(QMargins(0, 1, 1, 0));
  this->xAxis->setVisible(false);
  this->yAxis->setVisible(false);

  // create navigation box
  _navigationBox = std::shared_ptr<QCPItemRect>(new QCPItemRect(this));
  _navigationBox->setPen(QPen(_boxBoarderColor));
  _navigationBox->setBrush(_boxColor);
  addItem(_navigationBox.get());
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

void Control::setData(QCPDataMap *data, double maxDataValue, double minDataValue, size_t maxKey, bool copy) {
  graph()->setData(data, copy);
  graph()->rescaleAxes();
  _maxSignalAmplitude = maxDataValue;
  _minSignalAmplitude = minDataValue;
  _xLimit = maxKey;
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
    if (left < 0 || right > _xLimit)
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
