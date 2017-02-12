/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_EVENTS_H
#define UANC_EVENTS_H

namespace uanc {
namespace util {
namespace event {

/** \brief This enumeration contains all events.
 *
 * These events get used by the event system to signal the
 * current event.
 */
enum Events : std::uint8_t {

  /** \brief Gets fired when a view gets scrolled.
   *
   * Event describes when a widget gets scrolled.
   */
      Scroll
};
}
}
}

#endif //UANC_EVENTS_H
