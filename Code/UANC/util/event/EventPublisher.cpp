//
// Created by markus on 02.02.17.
//

#include "EventPublisher.h"

namespace uanc { namespace util { namespace event {

void EventPublisher::trigger(Events event, EventContainer data) {
  EventManager::get()->trigger(this, event, data);
}

EventPublisher::EventPublisher(int index) {
  this->_index = index;
}

EventPublisher* EventPublisher::Create(int index) {
  return new EventPublisher(index);
}
}}}
