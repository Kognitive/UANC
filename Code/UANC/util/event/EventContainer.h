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

#ifndef CODE_UANC_UTIL_EVENT_EVENTCONTAINER_H_
#define CODE_UANC_UTIL_EVENT_EVENTCONTAINER_H_

#include <string>
#include <map>
#include <utility>

namespace uanc {
namespace util {
namespace event {

/** \brief This is the event container.
 *
 * This class describes the event container, in which
 * your data gets wrapped when firing an event.
 */
class EventContainer {
 private:
  /** \brief Holds a map for the properties.
   *
   * This mapping holds a string to string mapping for the properties
   * of the event.
   */
  std::map<std::string, std::string> properties;

 public:
  /** Holds the id for the callee. */
  int ID = -1;

  /** \brief Adds a key to the container.
   *
   * This function takes a key and a value and adds it internally.
   *
   * @param key The key to add.
   * @param value The value to add.
   */
  void add(std::string key, std::string value) {
    this->properties.insert(std::make_pair(key, value));
  }

  /** \brief Retrieves a key from the internal map.
   *
   * @param key The key to retrieve.
   * @return The value matching the key
   */
  std::string get(std::string key) {
    return this->properties.at(key);
  }
};

}  // namespace event
}  // namespace util
}  // namespace uanc

#endif  // CODE_UANC_UTIL_EVENT_EVENTCONTAINER_H_
