//
// Created by markus on 02.02.17.
//

#ifndef UANC_EVENTTOKEN_H
#define UANC_EVENTTOKEN_H

#include <memory>
#include "Events.h"
#include "EventContainer.h"
#include "EventManager.h"

namespace uanc { namespace util { namespace event {

class EventToken {

  // Add the Event Manager as friend.
  friend class EventManager;
  friend class EventObserver;

 public:
  void trigger(Events event, EventContainer data);

 private:

  int _index;

  EventToken(int index);

  static EventToken* Create(int index);

  void subscribe(std::vector<Events> events);
};
}}}

#endif //UANC_EVENTTOKEN_H
