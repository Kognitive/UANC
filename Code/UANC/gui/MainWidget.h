/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_MAINWIDGET_H
#define UANC_MAINWIDGET_H

#include <QtWidgets/QWidget>
#include <memory>
#include "Code/libs/aquila/source/SignalSource.h"

namespace uanc {
namespace gui {

class MainWidget : public QWidget {

 public:

    /** \brief Basically places an input signal inside of the widget.
     *
     * This sets an input signal inside of the widget
     * @param signalSource the signal source to set
     */
    void setSignalInputSource(std::shared_ptr<Aquila::SignalSource> signalSource) {
      _signalSource = signalSource;
    }

    /** \brief Gets the output signal of the widget.
     *
     * This method gets the output signal of the method.
     * @return The signal source of the output
     */
    std::shared_ptr<Aquila::SignalSource> getSignalOutputSource() {
      return _signalSource;
    }

 private:

   /** \brief This holds the signalSource field.
    *
    * Simply holds the signal source field.
    */
   std::shared_ptr<Aquila::SignalSource> _signalSource;
};

}}
#endif //UANC_MAINWIDGET_H
