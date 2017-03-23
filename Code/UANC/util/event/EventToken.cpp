/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <Code/UANC/util/GlobalSettings.h>
#include "EventToken.h"

namespace uanc {
namespace util {
namespace event {

/** \brief Basic constructor of token.
  *
  * This constructor simply saves the supplied index inside. Note that
  * the index mustn't be changed anymore.
  *
  * @param index The unqiue index of this token.
  */
EventToken::EventToken(int index) {
  this->_index = index;
  this->_tabID = uanc::util::GlobalSettings::get()->currentIndex;
}

/** Destruct Event Token. */
void EventToken::destruct() {
  EventManager::get()->unregister(this->_index);
}

/** Can be used to get the last event */
EventContainer EventToken::getLastEvent(Events event) {
  return EventManager::get()->getLastEvent(this->_tabID, event);
}

/** Can be used to get the last event */
bool EventToken::hasLastEvent(Events event) {
  return EventManager::get()->hasLastEvent(this->_tabID, event);
}

/** \brief Creates an event.
 *
 * This method simply creates a new token with the supplied index.
 * It then returns this created token. Token should only created
 * via this function.
 *
 * @param index The unique index of this token.
 * @return Pass back the ready created token.
 */
EventToken *EventToken::Create(int index) {
  return new EventToken(index);
}

/** \brief Call this method to trigger an event.
 *
 * This can be called to trigger an event. Therefore you need to supply an event
 * and a data container.
 *
 * @param event The event to trigger.
 * @param data The data to pass with the event.
 */
void EventToken::trigger(Events event, EventContainer data) {
  data.ID = _tabID;
  EventManager::get()->trigger(this, event, data);
}

/** \brief Subscribe to an event.
 *
 * This method is used internally to subscribe to an event.
 *
 * @param events The events to subscribe to.
 */
void EventToken::subscribe(std::vector<Events> events) {
  for (auto val : events) {
    EventManager::get()->subscribe(val, this);
  }
}
}
}
}
