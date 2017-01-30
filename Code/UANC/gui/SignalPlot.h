//
// Created by jannewulf on 12.12.16.
//

#ifndef UANC_SIGNALPLOT_H
#define UANC_SIGNALPLOT_H

#include <memory>
#include <Code/libs/qplot/qcustomplot.h>

#include "PlotWidget.h"

namespace uanc {
namespace gui {

class PlotWidget;

class SignalPlot : public QCustomPlot {

 Q_OBJECT

 public:
  SignalPlot(std::shared_ptr<PlotWidget> parent);

  void setData(QCPDataMap *data, bool copy = false);
  void setError(QCPDataMap *error, bool copy = false);

  void setRange(double lower, double upper);

 public slots:
  void hideError(bool hide);

 private slots:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  /** \brief Holds reference to the parent widget
   *
   */
  std::shared_ptr<PlotWidget> _parent;

  /** \brief Holds the color for the plot
   *
   * Holds the QColor for the plot.
   */
  QColor _graphColor;

  std::shared_ptr<QCPItemStraightLine> _zoomLineOrigin, _zoomLineTarget;

  int _pressedX = -1, _pressedY = -1;

  const double _ZOOMFACTOR = 1.5;
  void zoom(double center);
  void unzoom(double center);
  void zoomRange(double press, double release);
  QCPRange scaleRange(double factor, double center);

  void setZoomLinePos(std::shared_ptr<QCPItemStraightLine> zoomLine, double xCoord);

  const int _SIGNAL = 0;
  const int _ERROR = 1;
};

}
}
#endif //UANC_SIGNALPLOT_H
