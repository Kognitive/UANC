/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SPECTROGRAMIEW_H
#define UANC_SPECTROGRAMIEW_H

#include <memory>
#include <QtWidgets/QWidget>
//QT-Stuff
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

#include <Code/UANC/amv/signal/model/SpectrogramModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/util/tools/Path.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/anc/model/ANCModel.h>

namespace uanc {
namespace amv {
namespace signal {
namespace view {


/** \brief 3D Plane view for a spectrogram.
 *
 */
using namespace QtDataVisualization;

class SpectrogramView : public uanc::amv::AlgorithmView<model::SpectrogramModel> {

 public:

  SpectrogramView()
      : m_graph3D(new Q3DSurface()),
        m_proxy3D(new QSurfaceDataProxy()),
        m_series3D(new QSurface3DSeries(m_proxy3D)),
        m_dataArray3D(new QSurfaceDataArray()) {

    m_series3D->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    m_series3D->setFlatShadingEnabled(true);
    m_graph3D->axisZ()->setLabelAutoRotation(30);
    m_graph3D->axisZ()->setTitle("Zeit in ms.");
    m_graph3D->axisZ()->setTitleVisible(true);
    m_graph3D->axisY()->setLabelAutoRotation(90);
    m_graph3D->axisY()->setTitle("FFT");
    m_graph3D->axisY()->setTitleVisible(true);
    m_graph3D->axisX()->setLabelAutoRotation(30);
    m_graph3D->axisX()->setTitle("sample Nr.");
    m_graph3D->axisX()->setTitleVisible(true);
    m_graph3D->axisX()->setAutoAdjustRange(true);


  }

  /**
   * Creates the widget for the 3D Spectrogram view
   * @return The widget for the 3D Spectrogram view
   */
  QWidget *produceWidget() final;

  void setData(std::shared_ptr<model::SpectrogramModel> data) final;

 private:
  Q3DSurface *m_graph3D;
  QSurfaceDataProxy *m_proxy3D;
  QSurface3DSeries *m_series3D;
  QSurfaceDataArray *m_dataArray3D;

};

}
}
}
}

#endif //UANC_SPECTROGRAMIEW_H
