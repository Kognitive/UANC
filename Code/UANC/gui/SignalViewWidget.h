//
// Created by markus on 26.01.17.
//

#ifndef UANC_SIGNALVIEWWIDGET_H
#define UANC_SIGNALVIEWWIDGET_H

#include <QtWidgets/QWidget>
#include <Code/UANC/amv/SignalModel.h>
#include <Code/UANC/amv/IAlgorithm.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QToolBar>
#include <Code/UANC/amv/signal/algorithm/IdentityTransformationAlgorithm.h>
#include <Code/UANC/amv/signal/TransformationAlgorithmRegister.h>

namespace uanc { namespace gui {

using namespace uanc::amv;

class SignalViewWidget : public QWidget {
 Q_OBJECT

 public:
  SignalViewWidget() {

  }

  void setSignalModel(const std::shared_ptr<SignalModel> &signalModel) {
    if (signalSet)
      throw new std::runtime_error("There was already a signal set. You have to create a new widget.");

    // save the original algorithm
    originalModel = signalModel;

    // basically initialize the gui
    this->layout = new QVBoxLayout;
    auto toolbar = new QToolBar;

    // create the toolbar with the entries from the register
    this->viewComboBox = new QComboBox;
    this->registeredViews = uanc::amv::signal::TransformationAlgorithmRegister::getTransformations();
    for(auto const& algorithm: *this->registeredViews.get())
    {
      this->viewComboBox->addItem(QString::fromStdString(algorithm->getName()));
    }

    toolbar->addWidget(this->viewComboBox);

    // create a action in the toolbar
    auto changeViewAction = toolbar->addAction("Change...");
    connect(changeViewAction, SIGNAL(triggered()), this, SLOT(changeView()));

    // add the toolbar widget
    this->layout->addWidget(toolbar);

    // initialize using the identity transformation
    this->registeredViews->at(currentSelected)->process(signalModel.get());

    // add the view from the algorithm to the layout
    this->widget = this->registeredViews->at(currentSelected)->getView()->getWidget();
    this->layout->addWidget(this->widget);
    setLayout(this->layout);

    // finally fill in the data
    registeredViews->at(currentSelected)->fillView();
  }


 private:
  bool signalSet = false;
  int currentSelected = 0;
  QComboBox* viewComboBox;
  QVBoxLayout* layout;
  QWidget* widget;
  std::shared_ptr<std::vector<IAlgorithm*>> registeredViews;
  std::shared_ptr<SignalModel> originalModel;

 public slots:
  void changeView() {

    // get the current index and return if nothing has changed
    auto cmbIndex = this->viewComboBox->currentIndex();
    if (cmbIndex == currentSelected)
      return;

    this->layout->removeWidget(this->widget);
    this->widget->hide();

    // new chosen cmbIndex is the new currentSelected Index value
    currentSelected = cmbIndex;

    // initialize using the identity transformation
    this->registeredViews->at(currentSelected)->process(this->originalModel.get());

    // add the view from the algorithm to the layout
    this->widget = this->registeredViews->at(currentSelected)->getView()->getWidget();
    this->layout->addWidget(this->widget);
    this->widget->show();

    // finally fill in the data
    registeredViews->at(currentSelected)->fillView();
  };
};
}}

#endif //UANC_SIGNALVIEWWIDGET_H
