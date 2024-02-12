#include "s21_controller.h"

#include <fstream>
#include <iostream>

namespace s21 {
Controller::Controller(Qt3DExtras::Qt3DWindow *view)
    : auxiliary_modules(new AuxiliaryModules()), view_(view) {}

Qt3DExtras::Qt3DWindow *Controller::getView() { return view_; }

void Controller::StartParsing(const std::string &filename,
                              Object &object_info) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return;
  }
  auxiliary_modules->ParserCounter(file, object_info);
  auxiliary_modules->ObjectParser(file, object_info);
}

Controller::~Controller() { delete auxiliary_modules; }
}  // namespace s21
