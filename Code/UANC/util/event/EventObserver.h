//
// Created by markus on 02.02.17.
//

#ifndef UANC_EVENTOBSERVER_H
#define UANC_EVENTOBSERVER_H

#include "EventContainer.h"
#include "EventManager.h"

namespace uanc { namespace util { namespace event {

class EventObserver {
 public:
  virtual void triggered(Events event, EventContainer data) = 0;
};
}}}

#endif //UANC_EVENTOBSERVER_H
