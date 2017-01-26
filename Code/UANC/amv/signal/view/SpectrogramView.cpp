/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <Code/UANC/gui/PlotWidget.h>
#include "SpectrogramView.h"
#include <iostream>

namespace uanc {
namespace amv {
namespace signal {
namespace view {

using namespace QtDataVisualization;

QWidget *SpectrogramView::produceWidget() {
    m_graph3D->addSeries(m_series3D);
    QWidget *container = QWidget::createWindowContainer(m_graph3D);
    return container;
}

void SpectrogramView::setData(model::SpectrogramModel *data) {

  //Update the data array of the class
   if (this->m_dataArray3D != nullptr) {
     delete this->m_dataArray3D;
   }

  //Convert the Aquila spectrogram into a QSurfaceDataArray
   m_dataArray3D = new QSurfaceDataArray();

  //TODO: Could be made faster

  //The Maximum value that the Y-Axis can have
  unsigned int maxYValue = 0;
  //Iterate over all frames
  for (int frame = 0 ; frame < data->spectrum->getFrameCount() ; frame++) {
    QSurfaceDataRow *newRow = new QSurfaceDataRow(data->spectrum->getSpectrumSize());
    int index = 0;

    //Iterate over all samples of a spectrum
    for (int sampleNr = 0; sampleNr < data->spectrum->getSpectrumSize(); sampleNr+= data->spectrum->getSpectrumSize()/200) {
      unsigned int yBuffer = std::abs(data->spectrum->getPoint(frame,sampleNr));
      maxYValue = ( maxYValue > yBuffer ) ? maxYValue : yBuffer;
      (*newRow)[index++].setPosition(QVector3D(sampleNr, yBuffer, frame*1000 ));
    }
    *m_dataArray3D << newRow;
  }
  m_proxy3D->resetArray(m_dataArray3D);

  //Set the range of the axis values
  m_graph3D->axisY()->setRange(0, maxYValue);
  m_graph3D->axisZ()->setRange(0, data->spectrum->getFrameCount()*1000);
  m_graph3D->axisX()->setRange(0, data->spectrum->getSpectrumSize());
  std::cout<<m_graph3D->axisX()->segmentCount()<<std::endl;
  std::cout<<m_graph3D->axisZ()->segmentCount()<<std::endl;
}

}
}
}
}
