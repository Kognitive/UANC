//
// Created by markus on 12/12/16.
//

#ifndef UANC_PLOTTER_H
#define UANC_PLOTTER_H

#include <Code/libs/qplot/qcustomplot.h>
#include <Code/libs/aquila/source/SignalSource.h>
#include <memory>

namespace uanc { namespace util { namespace tools {
  class QCustomPlotAdapter {
   public:
    static void plotSignal(std::shared_ptr<Aquila::SignalSource> signal, QCustomPlot* plot) {
      // convert the signal to a QVector
      auto samplesCount = signal->getSamplesCount();
      QVector<double> x(samplesCount), y(samplesCount);
      for (std::size_t i = 0; i < samplesCount; i = i + 10) {
        x[i] = i;
        y[i] = signal->sample(i);
      }

      // plot the signal
      auto graph = plot->addGraph();

      graph->setPen(QPen(Qt::blue));
      graph->setData(x, y);
      graph->rescaleAxes();

      plot->replot();
    }
  };
}}}



#endif //UANC_PLOTTER_H
