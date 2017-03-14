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
class SignalFileActor : FileActor<InvertedModel> {

 public:
  /** \brief Basic constructor which saves a path string internally.
   *
   * This constructor just save the passed string internally.
   *
   * @param path The path to the acted file
   */
  SignalFileActor(const std::string &path) : FileActor<InvertedModel>(path) {}

  /** \brief This method should load the file from the plate.
   *
   * This method should return the loaded T
   *
   * @return the loaded T
   */
  std::shared_ptr<InvertedModel> loadData() {
    //TODO: There should be an exception thrown, if the path is incorrect
    auto path = this->getPath();
    auto lwave = new Aquila::WaveFile(path, Aquila::StereoChannel::LEFT);
    auto rwave = new Aquila::WaveFile(path, Aquila::StereoChannel::RIGHT);
    auto model = new InvertedModel();
    model->left_channel = std::shared_ptr<Aquila::SignalSource>(lwave);
    model->right_channel = std::shared_ptr<Aquila::SignalSource>(rwave);
    return std::shared_ptr<InvertedModel>(model);
  }

  /** \brief This method should save a file to the plate.
   *
   * This should method should save the passed T
   * to the specified path.
   *
   * @param source The source to save
   */
  void saveData(std::shared_ptr<InvertedModel> source) {
    auto path = this->getPath();
    Aquila::WaveFile::save(*source->left_channel, path);
  }
};
}
}
#endif //UANC_SIGNALFILEACTOR_H
