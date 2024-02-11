#ifndef CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_

#include <string>

#include "../backend/auxiliary_modules.h"

class Controller {
 public:
  Controller() = default;

  void StartParsing(const std::string &filename, Object &object_info);
};

#endif  // CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_
