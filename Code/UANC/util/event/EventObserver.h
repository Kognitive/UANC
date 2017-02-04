//
// Created by markus on 02.02.17.
//

#ifndef UANC_EVENTOBSERVER_H
#define UANC_EVENTOBSERVER_H

#include "EventContainer.h"
#include "EventManager.h"
#include "EventToken.h"

namespace uanc { namespace util { namespace event {

class EventToken;


  class EventObserver {

    friend class EventManager;

   private:
    std::vector<Events> _events;

   protected:
    template<Events... ev>
    EventObserver();

    std::unique_ptr<EventToken> _token;
    virtual void triggered(Events event, EventContainer data) = 0;
  };

}}}


#endif //UANC_EVENTOBSERVER_H
