/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "EventObserver.h"

namespace uanc {
namespace util {
namespace event {

/** \brief Constructor for observing the event.
 *
 * This constructor can be used register all neccessary events inside.
 *
 * @param events The events to register.
 */
EventObserver::EventObserver(std::initializer_list<Events> events) {
  this->_token = EventManager::get()->listen(this);
  this->_token->subscribe(events);
}

}
}
}
