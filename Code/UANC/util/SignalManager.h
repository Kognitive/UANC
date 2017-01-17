//
// Created by markus on 12/12/16.
//

#ifndef UANC_SIGNALMANAGER_H
#define UANC_SIGNALMANAGER_H

#include "Code/libs/aquila/source/SignalSource.h"

#include <list>
#include <memory>
#include <map>

namespace uanc {
namespace util {

using namespace util;
using namespace std;

class SignalManager {
 private:
  /** \brief Map used to store the signals.
   *
   * This field gets used to save the signals inside of a map.
   */
  std::map<int, std::shared_ptr<Aquila::SignalSource>> signalsMap;

 public:

  /** \brief Shared pointer of the one and only instance of MainWindow.
   *
   * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
   * there are no dangling pointer referring to MainWindow.
   */
  static std::shared_ptr<SignalManager> _instance;

  /**  First of all define an abbreviation for the input signal. */
  static const std::string INPUT_SIGNAL;

  /** Afterwards define a string for the output signal. */
  static const std::string OUTPUT_SIGNAL;

  /** \brief Private constructor to deny creation outside of the singleton pattern.
    *
    * This constructor takes a QApplication and saves it internally as it context.
    */
  SignalManager();

  /** \brief Adds a signal to the internal map.
   *
   * Simply takes a string and a signal source and add them insidie of
   * the map.
   *
   * @param signalSource the signal source to adnamed.
   */
  int addSignal(const Aquila::SignalSource &signalSource);

  /** Simpel signal counter */
  int signalCounter = -1;

  /** \brief Adds a signal to the internal map.
   *
   * Simply takes a string and a signal source and add them insidie of
   * the map.
   *
   * @param identifier the identifier of the signal.
   * @param signalSource the signal source to adnamed.
   */
  int addSignal(std::shared_ptr<Aquila::SignalSource> signalSource);

  /** \brief This method returns a signal as a weak ptr.
   *
   * Return a weak pointer, pointing to the desired signal inside
   * if the manager
   *
   * @param name The name of the signal.
   *
   * @return It returns a weak pointer of aquilla sinal osource with
   * the speiciged name.
   */
  std::shared_ptr<Aquila::SignalSource> getSignal(int name);

  /** \brief Obtain a reference to the main window.
 *
 * Uses a classical singleton pattern to give back exactly the same copy of the main window.
 * In addition it uses a shared pointer.
 *
 * @return The shared pointer containing the MainWindow
 */
  static std::shared_ptr<SignalManager> get();
};

}
}

#endif //UANC_SIGNALMANAGER_H
