#include "s21_controller.h"

#include <fstream>
#include <iostream>

namespace s21 {
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
}  // namespace s21