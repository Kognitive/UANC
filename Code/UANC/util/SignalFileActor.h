/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SIGNALFILEACTOR_H
#define UANC_SIGNALFILEACTOR_H

#include <string>
#include <memory>
#include <Code/libs/aquila/source/SignalSource.h>
#include "FileActor.h"

namespace uanc { namespace util {

/** \brief Basic Signal file loader class.
 *
 * Is derived from the file loader class itself.
 */
class SignalFileActor : FileActor<Aquila::SignalSource> {

 public:
  /** \brief Basic constructor which saves a path string internally.
   *
   * This constructor just save the passed string internally.
   *
   * @param path The path to the acted file
   */
  SignalFileActor(const std::string& path) : FileActor<Aquila::SignalSource>(path) { }

  /** \brief This method should load the file from the plate.
   *
   * This method should return the loaded T
   *
   * @return the loaded T
   */
  std::shared_ptr<Aquila::SignalSource> loadData() {
    auto path = this->getPath();
    //TODO Wave laden
  }

  /** \brief This method should save a file to the plate.
   *
   * This should method should save the passed T
   * to the specified path.
   *
   * @param source The source to save
   */
  void saveData(std::shared_ptr<Aquila::SignalSource> source) {
    auto path = this->getPath();
    // TODO Wave speichern
  }
};
}}
#endif //UANC_SIGNALFILEACTOR_H
