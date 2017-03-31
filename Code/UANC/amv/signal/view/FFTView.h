/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CODE_UANC_AMV_SIGNAL_VIEW_FFTVIEW_H_
#define CODE_UANC_AMV_SIGNAL_VIEW_FFTVIEW_H_

#include <memory>
#include <QtWidgets/QWidget>
#include <Code/UANC/amv/InvertedModel.h>
#include <Code/UANC/amv/AlgorithmView.h>
#include <Code/UANC/gui/PlotWidget.h>
#include <Code/UANC/amv/signal/model/FFTModel.h>

namespace uanc {
namespace amv {
namespace signal {
namespace view {

using namespace uanc::amv::signal;

/** \brief Represents a SignalView.
 *
 * This represents a SignalView for FFT. It operates on an FFTSignalModel.
 * It basically shows a plot of the FFT of the signal.
 */
class FFTView : public amv::AlgorithmView <model::FFTModel> {
 public:

  /** \brief Gets the complete widget.
   *
   * This function is used to retrieve the widget from the view. It gets
   * used for integration the main application. It creates a Plotwidget inside
   * of a QWidget and passes this back.
   *
   * @return The created widget.
   */
  QWidget *produceWidget() final;

  /** \brief This method applies the model data.
  *
  * This method simply takes the passed data and places it inside of the
  * view.
  *
  * @param data The applied data.
  */
  void setData(std::shared_ptr<model::FFTModel> data) final;

 private:

  /** \brief Holds a reference to the plot widget used inside.
   *
   * This field holds a unqiue reference to the internally used plot widget.
   */
  uanc::gui::PlotWidget *_plotWidget;

};

}
}
}
}

#endif /* CODE_UANC_AMV_SIGNAL_VIEW_FFTVIEW_H_ */
