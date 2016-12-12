//
// Created by markus on 12/12/16.
//

#include "SignalManager.h"

namespace uanc { namespace util {

  /** \brief Shared pointer of the one and only instance of MainWindow.
   *
   * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
   * there are no dangling pointer referring to MainWindow.
   */
  std::shared_ptr<SignalManager> SignalManager::_instance = NULL;


  /** \brief Private constructor to deny creation outside of the singleton pattern.
    *
    * This constructor takes a QApplication and saves it internally as it context.
    */
  SignalManager::SignalManager() {

  }


  /** \brief Adds a signal to the internal map.
   *
   * Simply takes a string and a signal source and add them insidie of
   * the map.
   *
   * @param identifier the identifier of the signal.
   * @param signalSource the signal source to adnamed.
   */
  int SignalManager::addSignal(const Aquila::SignalSource& signalSource) {
    this->signalCounter = this->signalCounter + 1;
    auto weakSignalSource = std::make_shared<Aquila::SignalSource>(signalSource);
    this->signalsMap.insert(std::make_pair(this->signalCounter, weakSignalSource));
    return this->signalCounter;
  }

/** \brief Adds a signal to the internal map.
 *
 * Simply takes a string and a signal source and add them insidie of
 * the map.
 *
 * @param signalSource the signal source to adnamed.
 */
int SignalManager::addSignal(std::shared_ptr<Aquila::SignalSource> signalSource) {
  this->signalCounter = this->signalCounter + 1;
  this->signalsMap.insert(std::make_pair(this->signalCounter, signalSource));
  return this->signalCounter;
}

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
  std::shared_ptr<Aquila::SignalSource> SignalManager::getSignal(int index) {
    return this->signalsMap.at(index);
  }


  /** \brief Obtain a reference to the main window.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the signal manager.
   * In addition it uses a shared pointer.
   *
   * @return The shared pointer containing the signal manager
   */
  std::shared_ptr<SignalManager> SignalManager::get() {
    if (!_instance) {
      _instance = std::make_shared<SignalManager>();
    }

  return _instance;
}
}}