//
// Created by markus on 26.01.17.
//

#ifndef UANC_SIGNALVIEWWIDGET_H
#define UANC_SIGNALVIEWWIDGET_H

#include <QtWidgets/QWidget>
#include <Code/UANC/amv/InvertedModel.h>
#include <Code/UANC/amv/IAlgorithm.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QToolBar>
#include <Code/UANC/amv/signal/algorithm/IdentityTransformationAlgorithm.h>
#include <Code/UANC/amv/signal/TransformationAlgorithmRegister.h>
#include <iostream>

namespace uanc {
namespace gui {

using namespace uanc::amv;

class SignalViewWidget : public QWidget, public EventObserver {
 Q_OBJECT

 public:

  /** Default constructore for the signal view widget.
   *
   * @param id The unique id of this widget.
   * @param hasError True, if it has error.
   */
  SignalViewWidget(bool hasError = true) : EventObserver({Events::ChangeView}), _error(hasError) {
  }


  /** This method sets the signal model internally.
   *
   * @param signalModel The signal model to set.
   */
  void setSignalModel(std::shared_ptr<InvertedModel> signalModel) {
    if (signalSet)
      throw new std::runtime_error("There was already a signal set. You have to create a new widget.");

    // save the left_channel algorithm
    this->originalModel = signalModel;

    // basically initialize the gui
    this->layout = new QVBoxLayout;

    if (_token->hasLastEvent(Events::ChangeView)) {
      currentSelected = atoi(_token->getLastEvent(Events::ChangeView).get("Index").c_str());
    }

    // create the toolbar with the entries from the register
    this->registeredViews = uanc::amv::signal::TransformationAlgorithmRegister::getTransformations();

    // initialize using the identity transformation
    this->registeredViews->at(currentSelected)->process(signalModel);

    // add the view from the algorithm to the layout
    this->widget = this->registeredViews->at(currentSelected)->getView()->getWidget();
    this->layout->addWidget(this->widget);
    setLayout(this->layout);

    // finally fill in the data
    registeredViews->at(currentSelected)->fillView();
    signalSet = true;
  }

  // Gets called when the event is triggered
  void triggered(Events event, EventContainer data) final {
    if (!signalSet) return;

    // retrieve fields from container.
    auto strIndex = data.get("Index");
    auto cmbIndex = atoi(strIndex.c_str());

    // wrong id, so we want no change.
    if (cmbIndex == currentSelected) return;

    // reove widget
    this->layout->removeWidget(this->widget);
    delete this->widget;

    // new chosen cmbIndex is the new currentSelected Index value
    currentSelected = cmbIndex;

    // initialize using the identity transformation
    auto clonedOne = this->registeredViews->at(currentSelected)->clone();
    clonedOne->process(this->originalModel);

    // add the view from the algorithm to the layout
    this->widget = clonedOne->getView()->getWidget();
    this->layout->addWidget(this->widget);

    // finally fill in the data
    clonedOne->fillView();
  }

 private:

  /** Holds state if signal was already set. */
  bool signalSet = false;

  /** Holds state if error is shown. */
  bool _error;

  /** Holds the current selected index. */
  int currentSelected = 0;

  /** Holds the unique id of this widget. */
  int _id;

  /** Simple view related fields */
  QVBoxLayout *layout;
  QWidget *widget;
  std::shared_ptr<std::vector<IAlgorithm *>> registeredViews;
  std::shared_ptr<InvertedModel> originalModel;
};
}
}

#endif //UANC_SIGNALVIEWWIDGET_H
