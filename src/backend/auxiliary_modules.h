#ifndef CPP4_3DVIEWER_V2_0_1_BACKEND_OBJECT_HANDLER_H_
#define CPP4_3DVIEWER_V2_0_1_BACKEND_OBJECT_HANDLER_H_

#include <fstream>
#include <string>
#include <vector>

#include "s21_matrix/s21_matrix_oop.h"

namespace s21 {
struct Vertex {
  double x, y, z;
  int vertex_number;
};

struct Polygon {
  std::vector<Vertex> vertices;
};

struct Object {
  std::vector<Polygon> polygons;
  int num_of_polygons;
  int num_of_vertices;

  Object() : num_of_polygons(0), num_of_vertices(0) {}
};

class AuxiliaryModules {
 public:
  AuxiliaryModules() = default;
  static int ParserCounter(std::ifstream &file, Object &object);
  static void ObjectParser(std::ifstream &file, Object &object);

  static void Move(float x, float y, float z, S21Matrix &cur_point,
                   S21Matrix &result);
  static void Rotate(float x, float y, float z, S21Matrix &cur_point,
                     S21Matrix &result);
  static void Scale(float x, float y, float z, S21Matrix &cur_point,
                    S21Matrix &result);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_BACKEND_OBJECT_HANDLER_H_
