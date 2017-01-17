//
// Created by jannewulf on 12.12.16.
//

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
  Control(std::shared_ptr<PlotWidget> parent);

  void setData(QCPDataMap *data, double maxDataValue, double minDataValue, size_t maxKey, bool copy = false);

  void updateNavBox(QCPRange signalZoomRange);

  double getBoxLeft();
  double getBoxRight();

 private slots:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  std::shared_ptr<PlotWidget> _parent;

  /** \brief Holds the colors for the plots
   *
   * Holds the QColors for the plots.
   */
  QColor _graphColor, _boxColor, _boxBoarderColor;

  std::shared_ptr<QCPItemRect> _navigationBox;

  /**
   * \brief Holds the maximum and minimum amplitude of the current signal
   *
   * Holds the maximum and minimum amplitude of the current signal.
   */
  double _minSignalAmplitude, _maxSignalAmplitude;
  size_t _xLimit;

  int _pressedX = -1;
  double _mousePressBoxPosLeft = -1.0, _mousePressBoxPosRight = -1.0;
  bool _pressedOnNavBox = false;

  bool cursorOnNavBox(QMouseEvent *event);
};

}
}

#endif //UANC_CONTROL_H
