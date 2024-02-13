#ifndef CPP4_3DVIEWER_V2_0_1_BACKEND_S21_AUXILIARY_MODULES_H_
#define CPP4_3DVIEWER_V2_0_1_BACKEND_S21_AUXILIARY_MODULES_H_

#include <fstream>
#include <string>
#include <vector>

#include "s21_transformation_strategy.h"

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
  void SetStrategy(TransformationStrategy *strategy) { strategy_ = strategy; }

  void ExecuteStrategy(float x, float y, float z, S21Matrix &cur_point,
                       S21Matrix &result) {
    if (strategy_ != nullptr) strategy_->Transform(x, y, z, cur_point, result);
  }
  static int ParserCounter(std::ifstream &file, Object &object);
  static void ObjectParser(std::ifstream &file, Object &object);

 private:
  TransformationStrategy *strategy_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_BACKEND_AUXILIARY_MODULES_H_
