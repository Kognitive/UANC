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

#ifndef UANC_FILELOADER_H
#define UANC_FILELOADER_H

#include <string>
#include <memory>

namespace uanc {
namespace util {

/** \brief Simple FileActor class, which can operate on a file.
 *
 * This class can be used to write to a file and save something
 * to that file of type S
 *
 * @tparam T the type of object the file actor can handle
 */
template<typename T>
class FileActor {

 public:
  /** \brief Basic constructor which saves a path string internally.
   *
   * This constructor just save the passed string internally.
   *
   * @param path The path to the acted file
   */
  FileActor(const std::string &path) {
    this->_path = path;
  }

  /** \brief This method should load the file from the plate.
   *
   * This method should return the loaded T
   *
   * @return the loaded T
   */
  virtual std::shared_ptr<T> loadData() = 0;

  /** \brief This method should save a file to the plate.
   *
   * This should method should save the passed T
   * to the specified path.
   *
   * @param source The source to save
   */
  virtual void saveData(std::shared_ptr<T> source) = 0;

 protected:

  /** \brief This method returns the path to the caller.
   *
   * This method can be used to obtain the inner saved path.
   *
   * @return the path to the file
   */
  std::string getPath() {
    return this->_path;
  }

 private:

  /** \brief Holds the path internally
   *
   * This field holds the path internally.
   */
  std::string _path;
};
}
}
#endif //UANC_FILELOADER_H
