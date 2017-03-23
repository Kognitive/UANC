/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_HEATVIEW_H
#define UANC_HEATVIEW_H

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>
#include <Code/libs/aquila/functions.h>

namespace uanc {
namespace amv {
namespace signal {
namespace view {


class HeatView : public uanc::amv::AlgorithmView<model::SpectrogramModel> {

 public:

  QWidget *produceWidget() final {
    auto container = new QWidget();
    auto layout = new QHBoxLayout();
    customPlotL = new QCustomPlot();
    customPlotR = new QCustomPlot();
    layout->addWidget(customPlotL);
    layout->addWidget(customPlotR);
    container->setLayout(layout);
    return container;
  }

  void setData(std::shared_ptr<model::SpectrogramModel> data) final {

    configPlot(customPlotL, data->left_spectrum);
    configPlot(customPlotR, data->right_spectrum);
  }

  void configPlot(QCustomPlot* plot, std::shared_ptr<Aquila::Spectrogram> spectrogramm) {
// configure axis rect:// this will also allow rescaling the color scale by dragging/zooming
    plot->xAxis->setLabel("Frames");
    plot->yAxis->setLabel("Frequency");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
    int nx = spectrogramm->getFrameCount();
    int ny = spectrogramm->getSpectrumSize();
    colorMap->data()->setSize(nx, ny / 2); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(0, nx), QCPRange(0, ny / 2)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double rx, ry, rz;

    //Iterate over all frames
    for (std::size_t x = 0; x < spectrogramm->getFrameCount(); ++x)
    {
      // output only half of the spectrogram, below Nyquist frequency
      for (std::size_t y = 0; y < spectrogramm->getSpectrumSize() / 2; ++y)
      {
        colorMap->data()->cellToCoord(x, y, &rx, &ry);
        Aquila::ComplexType point = spectrogramm->getPoint(x, y);
        rz = Aquila::dB(point);
        colorMap->data()->setCell(x, y, rz);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(plot);
    plot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Spektrogramm");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpSpectrum);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    plot->rescaleAxes();
    plot->yAxis->setRange(0, ny / 2);
    plot->xAxis->setRange(0, nx);
    plot->replot();
  }
 private:
 QCustomPlot* customPlotL;
  QCustomPlot* customPlotR;
};

}
}
}
}

#endif //UANC_HEATVIEW_H
