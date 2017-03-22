//
// Created by jannewulf on 12.12.16.
//

#ifndef UANC_PLOTWIDGET_H
#define UANC_PLOTWIDGET_H

#include <QtWidgets/QWidget>
#include <memory>
#include <Code/UANC/amv/InvertedModel.h>
#include <Code/UANC/util/event/EventObserver.h>
#include "SignalPlot.h"
#include "Control.h"

namespace uanc
{
namespace gui
{

using namespace uanc::util::event;

class SignalPlot;
class Control;

class PlotWidget : public QWidget, public EventObserver
{

Q_OBJECT

public:
    /**
     * Contructor
     */
    PlotWidget();

    /** \brief This method is for setting a Signal.
     * This method is for setting a Signal. The Signal will immediately be plotted.
     *
     * @param signal The \ref Aquila::SignalSource which will be plotted
     */
    void
    setSignal(std::shared_ptr<uanc::amv::InvertedModel> signal);

    /** \brief Returns the current range of the x axis of the plot.
     *
     * @return Current range of the x axis of the plot.
     */
    const QCPRange
    getPlotXRange() const;

    /** \brief This method is for triggering the control to update because the plot changed.
     *
     */
    void
    plotChanged();

    /** \brief This method is for triggering the plot to update because the state of the control changed.
     *
     */
    void
    controlChanged();

    std::shared_ptr<uanc::amv::SignalModel>
    signal() { return _signal; }
    std::shared_ptr<uanc::amv::SignalModel>
    errorSignal() { return _errorSignal; }

    double
    lastIndex() { return _lastIndex; }

private:
    /**
     * \brief Holds the \ref QCustomPlot for the signal plot.
     */
    SignalPlot* _signalPlot;

    /**
     * \brief Holds the \ref QCustomPlot for the control.
     */
    Control* _control;

    /**
     * \brief True if checkbox for error curve should be shown, else false
     */
    bool _chkShown = false;

    QVBoxLayout *_layout;

    /**
     * \brief Hold the checkbox for showing the error
     */
    QCheckBox* _chkBoxShowError;

    /**
     * \brief Holds the plotted signal.
     */
    std::shared_ptr<uanc::amv::SignalModel> _signal, _errorSignal;

    double _lastIndex;

    /**
     * \brief This method initializes the plots.
     */
    void
    initialize();

    void
    triggered(Events event, EventContainer data) final;

    void
    triggerConnectedWidgets(QCPRange range);
};

}
}
#endif //UANC_PLOTWIDGET_H
