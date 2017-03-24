//
// Created by markus on 23.03.17.
//

#ifndef UANC_HEATWIDGET_H
#define UANC_HEATWIDGET_H

#include <Code/libs/qplot/qcustomplot.h>
#include <Code/UANC/util/event/EventObserver.h>
#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/libs/aquila/functions.h>
#include <Code/UANC/util/event/Events.h>
#include <Code/UANC/util/event/EventContainer.h>
#include <iostream>
namespace uanc
{
namespace gui {

using namespace uanc::util::event;
using namespace uanc::amv::signal::model;

class HeatWidget : public QCustomPlot, EventObserver {


 private:
  std::shared_ptr<SpectrogramModel> _data;

  /** Holds whether the widget was initialized, in the sense, that the data
   * was set already and is now saved inside.
   */
  bool _initialized = false;
  QCPColorScale *_colorScale;

  void switchChannel(int channel) {
    if (channel == 0) {
      configPlot(_data->left_spectrum);
    } else {
      configPlot(_data->right_spectrum);
    }
  }

public:
  HeatWidget() : EventObserver({Events::ChangeChannel}) {

    // add a color scale:
    _colorScale = new QCPColorScale(this);
    this->plotLayout()->addElement(0, 1, _colorScale);

  }

  void setData(std::shared_ptr<SpectrogramModel> data) {
    _data = data;
    _initialized = true;
    int channel = 0;
    if (_token->hasLastEvent(Events::ChangeChannel)) {
      channel = atoi(_token->getLastEvent(Events::ChangeChannel).get("Index").c_str());
    }

    switchChannel(channel);
}


  void configPlot(std::shared_ptr<Aquila::Spectrogram> spectrogramm) {

    // configure axis rect:// this will also allow rescaling the color scale by dragging/zooming
    this->xAxis->setLabel("Frames");
    this->yAxis->setLabel("Frequency");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(this->xAxis, this->yAxis);
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

    // add it to the right of the main axis rect
    _colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(_colorScale); // associate the color map with the color scale
    _colorScale->axis()->setLabel("Spektrogramm");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpSpectrum);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(this);
    this->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    _colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    this->rescaleAxes();
    this->yAxis->setRange(0, ny / 2);
    this->xAxis->setRange(0, nx);
    this->replot();
  }

  void triggered(Events event, EventContainer data) {
    if (!_initialized) return;

    if (event == Events::ChangeChannel) {
      int index = atoi(data.get("Index").c_str());
      switchChannel(index);
    }
  }
};
}
}

#endif //UANC_HEATWIDGET_H
