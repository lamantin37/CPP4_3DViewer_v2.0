#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "../backend/auxiliary_modules.h"

class Controller {
 public:
  Controller();

  void StartParsing(const std::string &filename, Object &objInfo);
};

#endif  // CONTROLLER_H
