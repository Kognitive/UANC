//
// Created by markus on 02.02.17.
//

#include "EventObserver.h"

namespace uanc {
namespace util {
namespace event {

template<Events... ev>
EventObserver::EventObserver() : _events(ev...) {
  this->_token = EventManager::get()->listen(this);
  this->_token->subscribe(_events);
}

}
}
}
