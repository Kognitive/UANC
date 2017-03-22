//
// Created by markus on 22.03.17.
//

#ifndef UANC_GLOBALSETTINGSBAR_H
#define UANC_GLOBALSETTINGSBAR_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QWidget>
#include <Code/UANC/amv/signal/TransformationAlgorithmRegister.h>
#include "../util/event/EventObserver.h"

namespace uanc {
namespace gui {

  // use necessary namespaces
  using namespace uanc::util::event;

  /** This class represents the global settings bar. It fires an event
   * so that all views can change.
   */
  class GlobalSettingsBar : public QWidget, public EventObserver {
   Q_OBJECT

   private:

    /** Holds the signal view bar. */
    QComboBox* _cmbSignal;

    /** Holds a unique identifier. */
    int _id;

    /** Simple initialization method for the gui. */
    void init() {

      // create the combobox
      _cmbSignal = new QComboBox();
      auto availableViews = uanc::amv::signal::TransformationAlgorithmRegister::getTransformations();
      for (auto const &algorithm: *availableViews) {
        _cmbSignal->addItem(QString::fromStdString(algorithm->getName()));
      }

      // connect to the slot in this module and apply
      // the layout internally.
      this->connect(_cmbSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(changedView(int)));

      // create the hLayout using the widgets
      auto hlayout = new QHBoxLayout();
      hlayout->addWidget(_cmbSignal);
      this->setLayout(hlayout);
    }

   public:

    /** Default constructor for the signal view change bar. */
    GlobalSettingsBar(int id) : EventObserver({Events::ChangeView}) {

      // call init
      _id = id;
      init();
    }

    /** This method gets called when one of the events was triggered. */
    void triggered(Events event, EventContainer data) final {

    }

    public slots:

      /** Slot if the view changed */
      void changedView(int index) {
        EventContainer container = EventContainer();
        container.add("ID", std::to_string(_id));
        container.add("Index", std::to_string(index));
        _token->trigger(Events::ChangeView, container);
      };

  };
}}

#endif //UANC_GLOBALSETTINGSBAR_H
