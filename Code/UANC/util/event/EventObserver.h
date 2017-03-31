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

#ifndef CODE_UANC_UTIL_EVENT_EVENTOBSERVER_H_
#define CODE_UANC_UTIL_EVENT_EVENTOBSERVER_H_

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

}  // namespace event
}  // namespace util
}  // namespace uanc

#endif  // CODE_UANC_UTIL_EVENT_EVENTOBSERVER_H_
