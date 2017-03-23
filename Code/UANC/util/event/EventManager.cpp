/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <iostream>
#include "EventManager.h"

namespace uanc {
namespace util {
namespace event {

std::shared_ptr<EventManager> EventManager::_instance;

/** \brief Basic constructor.
 *
 * This constructor fills the internal list with an initial value.
 */
EventManager::EventManager() {

  // Create the two mappings.
  _eventMapping = std::unique_ptr<std::unordered_map<Events, std::vector<int> *>>(
      new std::unordered_map<Events, std::vector<int> *>()
  );

  // Creaate empty id mapping
  _idMapping = std::unique_ptr<std::unordered_map<int, EventObserver *>>(
      new std::unordered_map<int, EventObserver *>()
  );

  // create empty start mapping
  _idEventMapping = std::unique_ptr<std::unordered_map<int, std::vector<Events> *>>(
      new std::unordered_map<int, std::vector<Events > *>()
  );

  cache = std::unique_ptr<Cache>(
     new Cache()
  );
}

/** \brief Basic destructor.
 *
 * This deconstructore destroys the registered instance.
 */
EventManager::~EventManager() {
  _destroyed = true;
  _idEventMapping->clear();
  _idMapping->clear();
  _eventMapping->clear();
}

/** \brief Obtain the reference to the EventManager.
 *
 * Uses a classical singleton pattern to give back exactly the same copy of the event manager.
 * In addition it uses a shared pointer.
 *
 * @return The shared pointer containing the event manager
 */
std::shared_ptr<EventManager> EventManager::get() {
  if (!_instance)
    _instance = std::shared_ptr<EventManager>(new EventManager());

  return _instance;
}

/** \brief Used to register an oberserver to an event.
 *
 * This method can be used to register an observer to register to events internally.
 *
 * @param event The event to listen to
 * @param observer The observer to listen to
 * @return The unique event publisher neccessary to publish messages.
 */
EventToken* EventManager::listen(EventObserver *observer) {

  // Basically increase the id counter by one
  this->_idCounter++;

  // First of all add the observer to the internal map
  this->_idMapping->insert(std::make_pair(_idCounter, observer));

  // Now create new vector and add ti idEventMapping
  auto eventVector = new std::vector<Events>();
  this->_idEventMapping->insert(std::make_pair(_idCounter, eventVector));

  // Now basically initialize a publisher and pass back
  auto publisher = EventToken::Create(_idCounter);

  // Pass back the result
  return publisher;
}

/** \brief Token calls this method to trigger an event.
 *
 * This method can be called from the outside to trigger an event.
 *
 * @param publisher The publisher event token.
 * @param event The event to trigger.
 * @param data The data to supply for this trigger.
 */
void EventManager::trigger(EventToken *publisher, Events event, EventContainer data) {
  // basically get the vector of all observer ids
  auto vec = this->_eventMapping->at(event);

  // add new map if no exists
  if (cache->count(std::make_pair(data.ID, event)) > 0) {
    cache->erase(std::make_pair(data.ID, event));
  }

  // insert event
  cache->insert(std::make_pair(std::make_pair(data.ID, event), data));


  // Now iterate overall values of the vector and initiate the events to the clients
  for (auto const &id: *vec) {
    if (id != publisher->_index) {
      auto observer = this->_idMapping->at(id);
      if (observer->_token->_tabID == data.ID) observer->triggered(event, data);
    }
  }
}

/** \brief Subsrcibe to an event.
   *
   * This method gets used to subscribe to an event. It can only be used by the corresponding token
   * because it is declared as friend.
   *
   * @param event The event to register.
   * @param token The token to register.
   */
void EventManager::subscribe(Events event, EventToken *token) {

  // reserve pointer
  std::vector<int> *pointer;

  // check if event list is already present
  if (this->_eventMapping->find(event) == this->_eventMapping->end()) {
    pointer = new std::vector<int>();
    this->_eventMapping->insert(std::make_pair(event, pointer));
  } else {
    pointer = this->_eventMapping->at(event);
  }

  // now add the pointer
  pointer->push_back(token->_index);

  // and add to event mapping
  _idEventMapping->at(token->_index)->push_back(event);
}

/** \brief Unregister token from the event manager.
  *
  * This method takes a token and degisters it from the event manager.
  * @param token The token to remove.
  */
void EventManager::unregister(int id) {
  if (_destroyed) return;

  auto eventList = _idEventMapping->at(id);

  // iterate over all registered events and remove matching
  // indices.
  for (auto &event : *eventList) {
    auto indexList = _eventMapping->at(event);
    for (auto it = indexList->begin(); it < indexList->end(); ++it) {
      if (*it == id) {
        indexList->erase(it);
      }
    }
  }

  // remove from id mapping
  _idMapping->erase(id);
  _idEventMapping->erase(id);
}

EventContainer EventManager::getLastEvent(int id, Events event) {
  return cache->at(std::make_pair(id, event));
}

bool EventManager::hasLastEvent(int id, Events event) {
  return cache->count(std::make_pair(id, event)) > 0;
}

}
}
}