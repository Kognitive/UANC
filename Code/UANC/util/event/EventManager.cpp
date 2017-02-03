//
// Created by markus on 02.02.17.
//

#include "EventManager.h"

namespace uanc { namespace util { namespace event {

  std::shared_ptr<EventManager> EventManager::_instance;

  EventManager::EventManager() {

    // Create the two mappings.
    _eventMapping = std::unique_ptr<std::map<Events, std::vector<int>*>>(
        new std::map<Events, std::vector<int>*>()
    );

    _idMapping = std::unique_ptr<std::map<int, EventObserver*>>(
        new std::map<int, EventObserver*>()
    );
  }

  /** \brief Obtain the reference to the EventManager.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the event manager.
   * In addition it uses a shared pointer.
   *
   * @return The shared pointer containing the event manager
   */
  std::shared_ptr<EventManager> EventManager::get() {
    if (!_instance) {
      _instance = std::shared_ptr<EventManager>(new EventManager());
    }

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
  std::unique_ptr<EventPublisher> EventManager::listen(Events event, EventObserver* observer) {

    // First of all add the observer to the internal map
    this->_idMapping->insert(std::make_pair(_idCounter, observer));

    // Get pointer and insert into event mapping
    std::vector<int>* pointer;
    if (this->_eventMapping->find(event) == this->_eventMapping->end()) {
      auto vec = new std::vector<int>();
      pointer = vec;
      this->_eventMapping->insert(std::make_pair(event, pointer));
    }
    else {
      pointer = this->_eventMapping->at(event);
    }

    // Add the id to the mapping to the pointer
    pointer->push_back(_idCounter);

    // Now basically initialize a publisher and pass back
    auto publisher = EventPublisher::Create(_idCounter);
    return std::unique_ptr<EventPublisher>(publisher);
  }

  void EventManager::trigger(EventPublisher* publisher, Events event, EventContainer data)
  {
    // basically get the vector of all observer ids
    auto vec = this->_eventMapping->at(event);

    // Now iterate overall values of the vector and initiate the events to the clients
    for(auto const& id: *vec) {
      if (id != publisher->_index) {
        auto observer = this->_idMapping->at(id);
        observer->triggered(event, data);
      }
    }
  }

}}}