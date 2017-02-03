//
// Created by markus on 02.02.17.
//

#ifndef UANC_EVENTPUBLISHER_H
#define UANC_EVENTPUBLISHER_H

#include <memory>
#include "Events.h"
#include "EventContainer.h"
#include "EventManager.h"

namespace uanc { namespace util { namespace event {

class EventPublisher {

  // Add the Event Manager as friend.
  friend class EventManager;

 public:
  void trigger(Events event, EventContainer data);

 private:

  int _index;

  EventPublisher(int index);

  static EventPublisher* Create(int index);
};
}}}

#endif //UANC_EVENTPUBLISHER_H
