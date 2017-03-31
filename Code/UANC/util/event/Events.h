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

#ifndef CODE_UANC_UTIL_EVENT_EVENTS_H_
#define CODE_UANC_UTIL_EVENT_EVENTS_H_

namespace uanc {
namespace util {
namespace event {

/** \brief This enumeration contains all events.
 *
 * These events get used by the event system to signal the
 * current event.
 */
enum class Events : uint8_t {
      /** \brief Gets fired when a view gets scrolled.
       *
       * Event describes when a widget gets scrolled.
       */
      Scroll = 0,

       /** Represents the change of a view. */
      ChangeView = 1,

      /** Represents the change of a channel. */
      ChangeChannel = 2,
};
}  // namespace event
}  // namespace util
}  // namespace uanc

#endif  // CODE_UANC_UTIL_EVENT_EVENTS_H_
