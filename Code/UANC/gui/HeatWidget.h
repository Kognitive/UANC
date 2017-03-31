/*
 * Copyright 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef CODE_UANC_GUI_HEATWIDGET_H_
#define CODE_UANC_GUI_HEATWIDGET_H_

#include <Code/libs/qplot/qcustomplot.h>
#include <Code/UANC/util/event/EventObserver.h>
#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/libs/aquila/functions.h>
#include <Code/UANC/util/event/Events.h>
#include <Code/UANC/util/event/EventContainer.h>
#include <memory>
#include <iostream>

namespace uanc {
namespace gui {

/** \brief Represents a heat widget.
 *
 * This class can be used as heat widget, to display a
 * spectrogram. */
class HeatWidget : public QCustomPlot, util::event::EventObserver {
 private:
  /** Holds the spectrogram model */
  std::shared_ptr<uanc::amv::signal::model::SpectrogramModel> _data;

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
    /** \brief Constructor of Control class
   *
   */
  HeatWidget() : EventObserver({util::event::Events::ChangeChannel}) {
    // add a color scale:
    _colorScale = new QCPColorScale(this);
    this->plotLayout()->addElement(0, 1, _colorScale);
  }

    /** \brief change channel to spectrogram
   *
     * @param data given spectrogram data
   */
  void setData(std::shared_ptr<
        uanc::amv::signal::model::SpectrogramModel> data) {
    _data = data;
    _initialized = true;
    int channel = 0;
    if (_token->hasLastEvent(util::event::Events::ChangeChannel)) {
      channel = atoi(
          _token->getLastEvent(util::event::Events::ChangeChannel)
              .get("Index").c_str());
    }

    switchChannel(channel);
}

    /** \brief plots spectogram
     *
     * configures the changes to show spectrogram
     *
     * @param spectrogramm given spectrogram
   */
  void configPlot(
        std::shared_ptr<Aquila::Spectrogram> spectrogramm) {
    // configure axis rect:
    // this will also allow rescaling the
    // color scale by dragging/zooming
    this->xAxis->setLabel("Frames");
    this->yAxis->setLabel("Frequency");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(this->xAxis, this->yAxis);
    int nx = spectrogramm->getFrameCount();
    int ny = spectrogramm->getSpectrumSize();

    // we want the color map to have nx * ny data points
    colorMap->data()->setSize(nx, ny / 2);

    // and span the coordinate range -4..4
    // in both key (x) and value (y) dimensions
    colorMap->data()->setRange(QCPRange(0, nx), QCPRange(0, ny / 2));

    // now we assign some data, by accessing
    // the QCPColorMapData instance of the color map:
    double rx, ry, rz;

    // Iterate over all frames
    for (std::size_t x = 0; x < spectrogramm->getFrameCount(); ++x) {
      // output only half of the spectrogram, below Nyquist frequency
      for (std::size_t y = 0; y < spectrogramm->getSpectrumSize() / 2; ++y) {
        colorMap->data()->cellToCoord(x, y, &rx, &ry);
        Aquila::ComplexType point = spectrogramm->getPoint(x, y);
        rz = Aquila::dB(point);
        colorMap->data()->setCell(x, y, rz);
      }
    }

    // add it to the right of the main axis rect
    // scale shall be vertical bar with tick
    // axis labels right (actually atRight is already the default)
    _colorScale->setType(QCPAxis::atRight);

    // associate the color map with the color scale
    colorMap->setColorScale(_colorScale);
    _colorScale->axis()->setLabel("Spektrogramm");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpSpectrum);
    // we could have also created a
    // QCPColorGradient instance and added own colors to
    // the gradient, see the documentation
    // of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that
    // all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale
    // synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(this);
    this->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    _colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    this->rescaleAxes();
    this->yAxis->setRange(0, ny / 2);
    this->xAxis->setRange(0, nx);
    this->replot();
  }
    /** \brief starts channelswitch when triggered by event
   *
     * @param event given event
     * @param data given events
   */
  void triggered(util::event::Events event, util::event::EventContainer data) {
    if (!_initialized) return;

    if (event == util::event::Events::ChangeChannel) {
      int index = atoi(data.get("Index").c_str());
      switchChannel(index);
    }
  }
};

}  // namespace gui
}  // namespace uanc

#endif  // CODE_UANC_GUI_HEATWIDGET_H_
