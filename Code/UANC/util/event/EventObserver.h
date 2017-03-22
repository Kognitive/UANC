/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_EVENTOBSERVER_H
#define UANC_EVENTOBSERVER_H

#include "EventContainer.h"
#include "EventManager.h"
#include "EventToken.h"

namespace uanc {
namespace util {
namespace event {

class EventToken;

/** \brief Represents the observer interface.
 *
 * This class is an event observer. Simply derive from
 * it to let a class access the event system.
 */
class EventObserver {

  friend class EventManager;

 protected:

  /** \brief Constructor for observing the event.
   *
   * This constructor can be used register all neccessary events inside.
   *
   * @param events The events to register.
   */
  EventObserver(std::initializer_list<Events> events);

  /** \brief Deconstructor
   *
   * This deconstructor can be used to deregister the token.
   */
  ~EventObserver();

  /** \brief Unique Pointer to the token.
   *
   * This can be used to access the token.
   */
  EventToken* _token;

  /** \brief Override to catch event.
   *
   * This can be used, to integrate a handling to a specific event.
   *
   * @param event The event which should be triggered.
   * @param data The data to supply.
   */
  virtual void triggered(Events event, EventContainer data) = 0;
};

}
}
}

#endif //UANC_EVENTOBSERVER_H
