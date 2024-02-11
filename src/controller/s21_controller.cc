#include "s21_controller.h"

#include <fstream>
#include <iostream>

void Controller::StartParsing(const std::string &filename,
                              Object &object_info) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return;
  }
  ParserCounter(file, object_info);
  ObjectParser(file, object_info);
}
