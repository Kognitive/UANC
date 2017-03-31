/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CODE_UANC_UTIL_EVENT_EVENTTOKEN_H_
#define CODE_UANC_UTIL_EVENT_EVENTTOKEN_H_

#include <memory>
#include <vector>
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

  /** Can be used to get the last event */
  EventContainer getLastEvent(Events event);

  /** Can be used to get the last event */
  bool hasLastEvent(Events event);

  /** Can be used to delete the last event. */
  void deleteLastEvent(Events event);

 private:
  /** \brief Current Index.
   *
   * This index is used to store the index of this token. The same
   * index gets used by the eventsystem to identify this token.
   */
  int _index;

  /** \brief Current Tab ID.
   *
   * This holds the tab id.
   */
  int _tabID;

  /** \brief Basic constructor of token.
   *
   * This constructor simply saves the supplied index inside. Note that
   * the index mustn't be changed anymore.
   *
   * @param index The unqiue index of this token.
   */
  explicit EventToken(int index);

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
}  // namespace event
}  // namespace util
}  // namespace uanc

#endif  // CODE_UANC_UTIL_EVENT_EVENTTOKEN_H_
