#ifndef CPP4_3DVIEWER_V2_0_1_BACKEND_S21_TRANSFORMATION_STRATEGY_H_
#define CPP4_3DVIEWER_V2_0_1_BACKEND_S21_TRANSFORMATION_STRATEGY_H_

#include <fstream>
#include <string>
#include <vector>

#include "s21_matrix/s21_matrix_oop.h"

namespace s21 {
class TransformationStrategy {
 public:
  virtual ~TransformationStrategy() = default;
  virtual void Transform(float x, float y, float z, S21Matrix &cur_point,
                         S21Matrix &result) = 0;
};

class MoveStrategy : public TransformationStrategy {
 public:
  void Transform(float x, float y, float z, S21Matrix &cur_point,
                 S21Matrix &result) override;
};

class RotateStrategy : public TransformationStrategy {
 public:
  void Transform(float x, float y, float z, S21Matrix &cur_point,
                 S21Matrix &result) override;
};

class ScaleStrategy : public TransformationStrategy {
 public:
  void Transform(float x, float y, float z, S21Matrix &cur_point,
                 S21Matrix &result) override;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_BACKEND_TRANSFORMATION_STRATEGY_H_
