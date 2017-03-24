/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_EVENTMANAGER_H
#define UANC_EVENTMANAGER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "EventToken.h"
#include "Events.h"
#include "EventObserver.h"


struct EventIDHash {
 public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ static_cast<std::size_t>(x.second);
  }
};

class EventIDEqual
{
 public:
  template <typename T, typename U>
  bool operator() (std::pair<T, U> const& t1, std::pair<T, U> const& t2) const
  {
    return t1.first == t2.first && t1.second == t2.second;
  }
};

namespace uanc {
namespace util {
namespace event {

class EventToken;
class EventObserver;

using Cache = std::unordered_map<std::pair<int, Events>, EventContainer, EventIDHash>;

/** \brief Simple event manager.
 *
 * This class represents the event manager and can be accessed via the singleton pattern
 * from all classes which are friends of this one.
 */
class EventManager {

  // Add the Event Publisher as friend.
  friend class EventToken;
  friend class EventObserver;

 public:

  /** \brief Basic destructor.
   *
   * This deconstructore destroys the registered instance.
   */
  ~EventManager();

  /** This method gets called to destroy the event manager. */
  static void destroy();

 private:

  /** Simple debug flag. */
  const bool DEBUG = true;

  /** \brief Basic constructor.
   *
   * This constructor fills the internal list with an initial value.
   */
  EventManager();

  /** \brief Token calls this method to trigger an event.
   *
   * This method can be called from the outside to trigger an event.
   *
   * @param publisher The publisher event token.
   * @param event The event to trigger.
   * @param data The data to supply for this trigger.
   */
  void trigger(EventToken *publisher, Events event, EventContainer data);

  /** \brief Shared pointer to the one and only instance of EventManager
   *
   * Holds a reference to the global event manager.
   */
  static EventManager* _instance;

  /**
    * Holds an unordered map over all events (Event, id(=vector<int>))
    */
  std::unique_ptr<std::unordered_map<Events, std::vector<int>*>> _eventMapping;
  /**
   * Holds an unordered map over all IDs (ID, events(=vector<Events>))
   */
  std::unique_ptr<std::unordered_map<int, std::vector<Events>*>> _idEventMapping;
  /**
   * Holds an unorderd map over all IDs and EventObserver
   */
  std::unique_ptr<std::unordered_map<int, EventObserver*>> _idMapping;

  // init counter for id to zero
  int _idCounter = 0;

  /**
   * Simple cache for the last event
   */

  std::unique_ptr<Cache> cache;

  /** True, iff the event manger was already destroyed. */
  bool _destroyed = false;

  /** \brief Obtain the reference to the EventManager.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the event manager.
   * In addition it uses a shared pointer.
   *
   * @return The shared pointer containing the event manager
   */
  static EventManager* get();

  /** \brief Used to register an oberserver to an event.
   *
   * This method can be used to register an observer to register to events internally.
   *
   * @param event The event to listen to
   * @param observer The observer to listen to
   * @return The unique event publisher neccessary to publish messages.
   */
  EventToken* listen(EventObserver *observer);

  /** \brief Subsrcibe to an event.
   *
   * This method gets used to subscribe to an event. It can only be used by the corresponding token
   * because it is declared as friend.
   *
   * @param event The event to register.
   * @param token The token to register.
   */
  void subscribe(Events event, EventToken *token);


/** \brief Return the last event
  *
  * This method returns the last event for a given id
  * @param ID to check for the event
  * @param Event to check for on ID
  */
  EventContainer getLastEvent(int id, Events event);

  /** \brief Checks if there was a last event
  *
  * This method checks if there is a last event for a given ID
  * @param ID to check for the event
  * @param Event to check for on ID
  */
  bool hasLastEvent(int id, Events event);

  /** \brief Deletes the last event
   *
   * This method deletes the last event for a given ID
   * @param ID to delete the event
   * @param Event to delete from ID
   */
  void deleteLastEvent(int id, Events event);

  /** \brief Unregister token from the event manager.
   *
   * This method takes a token and degisters it from the event manager.
   * @param token The token to remove.
   */
  void unregister(int tokenid);
};
}
}
}

#endif //UANC_EVENTMANAGER_H
