/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_EVENTCONTAINER_H
#define UANC_EVENTCONTAINER_H

#include <map>

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
  std::map<std::string, std::string> properties = std::map<std::string, std::string>();

 public:

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
}
}
}

#endif //UANC_EVENTCONTAINER_H
