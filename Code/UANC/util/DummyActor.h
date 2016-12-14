//
// Created by jannewulf on 01.12.16.
//

#ifndef UANC_DUMMYACTOR_H
#define UANC_DUMMYACTOR_H

#include <string>
#include <memory>
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/libs/aquila/source/generator/Generator.h"
#include "Code/libs/aquila/source/generator/SineGenerator.h"
#include "Code/libs/aquila/source/generator/TriangleGenerator.h"
#include "FileActor.h"

namespace uanc {
namespace util {

class DummyActor : FileActor<Aquila::SignalSource> {

 public:
  /** \brief Basic constructor which saves a path string internally.
   *
   * This constructor just save the passed string internally.
   *
   * @param path The path to the acted file
   */
  DummyActor(const std::string &path) : FileActor<Aquila::SignalSource>(path) {

  }

  /** \brief This method should load the file from the plate.
   *
   * This method should return the loaded T
   *
   * @return the loaded T
   */
  std::shared_ptr<Aquila::SignalSource> loadData() {
    if (type == "sine")
      return this->sineSignal();
    else if (type == "triangle")
      return this->triangleSignal();
  }

  /** \brief This method should save a file to the plate.
   *
   * This should method should save the passed T
   * to the specified path.
   *
   * @param source The source to save
   */
  void saveData(std::shared_ptr<Aquila::SignalSource> source) {}

  DummyActor* setType(std::string type) {
    if (type == "sine") {
      this->type = type;
      return this;
    } else if (type == "triangle") {
      this->type = type;
      return this;
    } else
      return NULL;
  }

  DummyActor* setFrequency(Aquila::FrequencyType frequency) {
    this->freq = frequency;
    return this;
  }

  DummyActor* setAmplitude(Aquila::FrequencyType amplitude) {
    this->amp = amplitude;
    return this;
  }

  DummyActor* setSampleCount(size_t count) {
    this->samples = count;
    return this;
  }

 private:
  std::string type;
  Aquila::FrequencyType freq;
  Aquila::FrequencyType amp;
  size_t samples;

  std::shared_ptr<Aquila::SignalSource> sineSignal() {
    Aquila::SineGenerator *generator = new Aquila::SineGenerator(this->samples * 100);
    generator->setFrequency(this->freq).setAmplitude(this->amp).generate(this->samples);
    return std::shared_ptr<Aquila::SignalSource>(generator);
  }

  std::shared_ptr<Aquila::SignalSource> triangleSignal() {
    Aquila::TriangleGenerator *generator = new Aquila::TriangleGenerator(this->samples * 100);
    generator->setFrequency(this->freq).setAmplitude(this->amp).generate(this->samples);
    return std::shared_ptr<Aquila::SignalSource>(generator);
  }
};

}
}

#endif //UANC_DUMMYACTOR_H
