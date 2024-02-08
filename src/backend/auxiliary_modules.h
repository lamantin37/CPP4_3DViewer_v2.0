#ifndef AUXILIARY_MODULES_H
#define AUXILIARY_MODULES_H

#include <cmath>
#include <fstream>

#include "s21_matrix/s21_matrix_oop.h"

constexpr int POLYGON_SIZE = 3;
constexpr int OK = 0;
constexpr int MATRIX_ERROR = 1;
constexpr int CALC_ERROR = 2;

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

void move(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result);
void rotate(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result);
void scale(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result);

int parser_counter(std::ifstream &file, Object &object);
void object_parser(std::ifstream &file, Object &object);

#endif  // AUXILIARY_MODULES_H
