/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

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
