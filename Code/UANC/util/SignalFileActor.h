/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_SIGNALFILEACTOR_H
#define UANC_SIGNALFILEACTOR_H

#include <string>
#include <memory>
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/libs/aquila/source/WaveFile.h"
#include "FileActor.h"

namespace uanc {
namespace util {

using namespace uanc::amv;

/** \brief Basic Signal file loader class.
 *
 * Is derived from the file loader class itself.
 */
class SignalFileActor : FileActor<SignalModel> {

 public:
  /** \brief Basic constructor which saves a path string internally.
   *
   * This constructor just save the passed string internally.
   *
   * @param path The path to the acted file
   */
  SignalFileActor(const std::string &path) : FileActor<SignalModel>(path) {}

  /** \brief This method should load the file from the plate.
   *
   * This method should return the loaded T
   *
   * @return the loaded T
   */
  std::shared_ptr<SignalModel> loadData() {
    auto path = this->getPath();
    auto wave = new Aquila::WaveFile(path);
    auto model = new SignalModel();
    model->original = std::shared_ptr<Aquila::SignalSource>(wave);
    return std::shared_ptr<SignalModel>(model);
  }

  /** \brief This method should save a file to the plate.
   *
   * This should method should save the passed T
   * to the specified path.
   *
   * @param source The source to save
   */
  void saveData(std::shared_ptr<SignalModel> source) {
    auto path = this->getPath();
    Aquila::WaveFile::save(*source->original, path);
  }
};
}
}
#endif //UANC_SIGNALFILEACTOR_H
