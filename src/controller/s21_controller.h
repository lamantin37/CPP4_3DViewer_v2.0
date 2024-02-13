#ifndef CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_

#include <string>

#include "../backend/s21_auxiliary_modules.h"

namespace s21 {
class Controller {
 public:
  Controller();
  ~Controller();

  void StartParsing(const std::string &filename, Object &object_info);

 private:
  AuxiliaryModules *auxiliary_modules_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_
