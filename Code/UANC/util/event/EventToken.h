/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_EVENTTOKEN_H
#define UANC_EVENTTOKEN_H

#include <memory>
#include "Events.h"
#include "EventContainer.h"
#include "EventManager.h"

namespace uanc {
namespace util {
namespace event {

/** \brief Token retrieved by the eventsystem.
 *
 * This token describes the access of a class to the eventsystem.
 * Every instance will be handled as a unqiue one.
 */
class EventToken {

  // Add the Event Manager as friend.
  friend class EventManager;
  friend class EventObserver;

 public:
  /** \brief Call this method to trigger an event.
   *
   * This can be called to trigger an event. Therefore you need to supply an event
   * and a data container.
   *
   * @param event The event to trigger.
   * @param data The data to pass with the event.
   */
  void trigger(Events event, EventContainer data);

 private:

  /** \brief Current Index.
   *
   * This index is used to store the index of this token. The same
   * index gets used by the eventsystem to identify this token.
   */
  int _index;

  /** \brief Basic constructor of token.
   *
   * This constructor simply saves the supplied index inside. Note that
   * the index mustn't be changed anymore.
   *
   * @param index The unqiue index of this token.
   */
  EventToken(int index);

  /** \brief Creates an event.
   *
   * This method simply creates a new token with the supplied index.
   * It then returns this created token. Token should only created
   * via this function.
   *
   * @param index The unique index of this token.
   * @return Pass back the ready created token.
   */
  static EventToken *Create(int index);

  /** \brief Subscribe to an event.
   *
   * This method is used internally to subscribe to an event.
   *
   * @param events The events to subscribe to.
   */
  void subscribe(std::vector<Events> events);

  /** Destruct Event Token. */
  void destruct();
};
}
}
}

#endif //UANC_EVENTTOKEN_H
