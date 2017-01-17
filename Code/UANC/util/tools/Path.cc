//
// Created by markus on 12/12/16.
//

#include "Path.h"

namespace uanc {
namespace util {

/** \brief Passes back the filename of the given path */
std::string Path::getFileName(std::string path) {
  char sep = '/';

#ifdef _WIN32
  sep = '\\';
#endif

  size_t i = path.rfind(sep, path.length());
  if (i != std::string::npos) {
    return (path.substr(i + 1, path.length() - i));
  }
}
}
}
