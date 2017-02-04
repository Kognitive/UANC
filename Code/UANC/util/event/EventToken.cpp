//
// Created by markus on 02.02.17.
//

#include "EventToken.h"

namespace uanc { namespace util { namespace event {

EventToken::EventToken(int index) {
  this->_index = index;
}

EventToken* EventToken::Create(int index) {
  return new EventToken(index);
}

void EventToken::trigger(Events event, EventContainer data) {
  EventManager::get()->trigger(this, event, data);
}

void EventToken::subscribe(std::vector<Events> events) {
  for (auto val : events) {
    EventManager::get()->subscribe(val, this);
  }
}
}}}
