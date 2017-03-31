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

#include "Code/UANC/util/event/EventObserver.h"

namespace uanc {
namespace util {
namespace event {

/** \brief Constructor for observing the event.
 *
 * This constructor can be used register all neccessary events inside.
 *
 * @param events The events to register.
 */
EventObserver::EventObserver(std::initializer_list<Events> events) {
  this->_token = EventManager::get()->listen(this);
  this->_token->subscribe(events);
}

/** \brief Deconstructor
  *
  * This deconstructor can be used to deregister the token.
  */
EventObserver::~EventObserver() {
  this->_token->destruct();
  delete this->_token;
}
}  // namespace event
}  // namespace util
}  // namespace uanc
