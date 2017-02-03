//
// Created by markus on 02.02.17.
//

#ifndef UANC_EVENTMANAGER_H
#define UANC_EVENTMANAGER_H

#include <memory>
#include <vector>
#include <map>
#include "EventPublisher.h"
#include "Events.h"
#include "EventObserver.h"

namespace uanc { namespace util { namespace event {

class EventPublisher;

class EventManager {

  // Add the Event Publisher as friend.
  friend class EventPublisher;

 private:

  EventManager();

  void trigger(EventPublisher* publisher, Events event, EventContainer data);

  /** \brief Shared pointer to the one and only instance of EventManager
   *
   * Holds a reference to the global event manager.
   */
  static std::shared_ptr<EventManager> _instance;

  std::unique_ptr<std::map<Events, std::vector<int>*>> _eventMapping;
  std::unique_ptr<std::map<int, EventObserver*>> _idMapping;

  // init counter for id to zero
  int _idCounter = 0;
 public:

  /** \brief Obtain the reference to the EventManager.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the event manager.
   * In addition it uses a shared pointer.
   *
   * @return The shared pointer containing the event manager
   */
  static std::shared_ptr<EventManager> get();

  /** \brief Used to register an oberserver to an event.
   *
   * This method can be used to register an observer to register to events internally.
   *
   * @param event The event to listen to
   * @param observer The observer to listen to
   * @return The unique event publisher neccessary to publish messages.
   */
  std::unique_ptr<EventPublisher> listen(Events event, EventObserver* observer);
};
}}}

#endif //UANC_EVENTMANAGER_H
