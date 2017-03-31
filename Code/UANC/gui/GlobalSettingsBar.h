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

#ifndef UANC_GLOBALSETTINGSBAR_H
#define UANC_GLOBALSETTINGSBAR_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QWidget>
#include <Code/UANC/amv/signal/TransformationAlgorithmRegister.h>
#include "../util/event/EventObserver.h"
#include <iostream>
#include "../util/GlobalSettings.h"

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

    /** Debug flag */
    const bool DEBUG = true;

    /** Holds the signal view bar. */
    QComboBox* _cmbSignal;

    /** Holds the combobox, which channel is displayed. */
    QComboBox* _cmbChannel;

    /** Holds a unique identifier. */
    int _id;

    /** Simple initialization method for the gui. */
    void init(bool hasRight) {

      // create the combobox
      _cmbSignal = new QComboBox();
      auto availableViews = uanc::amv::signal::TransformationAlgorithmRegister::getTransformations();
      for (auto const &algorithm: *availableViews) {
        _cmbSignal->addItem(QString::fromStdString(algorithm->getName()));
      }

      // create left right combobox
      _cmbChannel = new QComboBox();
      _cmbChannel->addItem("Left");
      if (hasRight) _cmbChannel->addItem("Right");

      // connect to the slot in this module and apply
      // the layout internally.
      this->connect(_cmbSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(changedView(int)));
      this->connect(_cmbChannel, SIGNAL(currentIndexChanged(int)), this, SLOT(changedChannel(int)));

      // create the hLayout using the widgets
      auto hlayout = new QHBoxLayout();
      hlayout->addWidget(_cmbSignal);
      hlayout->addWidget(_cmbChannel);
      this->setLayout(hlayout);
    }

   public:

    /** Default constructor for the signal view change bar. */
    GlobalSettingsBar(int hasRight) : EventObserver({Events::ChangeView, Events::ChangeChannel, Events::Scroll}) {

      // call init
      _id = uanc::util::GlobalSettings::get()->currentIndex;

      init(hasRight);
    }

    ~GlobalSettingsBar() {
      _token->deleteLastEvent(Events::ChangeView);
      _token->deleteLastEvent(Events::ChangeChannel);
      _token->deleteLastEvent(Events::Scroll);
    }

    /** This method gets called when one of the events was triggered. */
    void triggered(Events event, EventContainer data) final {

    }

    public slots:

      /** Slot if the view changed */
      void changedView(int index) {
        EventContainer container = EventContainer();
        container.add("Index", std::to_string(index));
        _token->deleteLastEvent(Events::Scroll);
        _token->trigger(Events::ChangeView, container);
      };

      /** Slot if channel changed */
      void changedChannel(int index) {
        EventContainer container = EventContainer();
        container.ID = _id;
        container.add("Index", std::to_string(index));
        _token->trigger(Events::ChangeChannel, container);
      }

  };
}}

#endif //UANC_GLOBALSETTINGSBAR_H
