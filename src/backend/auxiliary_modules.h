#ifndef CPP4_3DVIEWER_V2_0_1_BACKEND_AUXILIARY_MODULES_H_
#define CPP4_3DVIEWER_V2_0_1_BACKEND_AUXILIARY_MODULES_H_

#include <cmath>
#include <fstream>

#include "s21_matrix/s21_matrix_oop.h"

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

void Move(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result);
void Rotate(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result);
void Scale(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result);

int ParserCounter(std::ifstream &file, Object &object);
void ObjectParser(std::ifstream &file, Object &object);

#endif  // CPP4_3DVIEWER_V2_0_1_BACKEND_AUXILIARY_MODULES_H_
