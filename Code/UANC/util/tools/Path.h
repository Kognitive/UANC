//
// Created by markus on 12/12/16.
//

#ifndef UANC_PATH_H
#define UANC_PATH_H

#include <string>

namespace uanc { namespace util {
  class Path {
   public:
    static std::string getFileName(std::string path);
  };
}}


#endif //UANC_PATH_H
