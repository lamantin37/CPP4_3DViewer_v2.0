#include "s21_controller.h"

#include <fstream>
#include <iostream>

Controller::Controller() {}

void Controller::StartParsing(const std::string &filename, Object &objInfo) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return;
  }
  ParserCounter(file, objInfo);
  ObjectParser(file, objInfo);
}
