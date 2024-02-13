#include "s21_controller.h"

#include <fstream>
#include <iostream>

namespace s21 {
Controller::Controller() : auxiliary_modules_(new AuxiliaryModules()) {}

void Controller::StartParsing(const std::string &filename,
                              Object &object_info) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return;
  }
  auxiliary_modules_->ParserCounter(file, object_info);
  auxiliary_modules_->ObjectParser(file, object_info);
}

Controller::~Controller() { delete auxiliary_modules_; }
}  // namespace s21
