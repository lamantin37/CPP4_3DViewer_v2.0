#include "auxiliary_modules.h"

void move(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result) {
  S21Matrix move_matrix(4, 4);
  move_matrix(0, 0) = move_matrix(1, 1) = move_matrix(2, 2) =
      move_matrix(3, 3) = 1;
  move_matrix(0, 3) = x;
  move_matrix(1, 3) = y;
  move_matrix(2, 3) = z;

  result = move_matrix * cur_point;
}

void rotate(float x, float y, float z, S21Matrix &cur_point,
            S21Matrix &result) {
  S21Matrix rotate_matrix(4, 4);
  for (int i = 0, j = 0; i < rotate_matrix.getRows(); i++, j++) {
    rotate_matrix(i, j) = 1;
  }

  if (x != 0) {
    rotate_matrix(1, 1) = cos(x);
    rotate_matrix(1, 2) = -sin(x);
    rotate_matrix(2, 1) = sin(x);
    rotate_matrix(2, 2) = cos(x);
  } else if (y != 0) {
    rotate_matrix(0, 0) = cos(y);
    rotate_matrix(0, 2) = sin(y);
    rotate_matrix(2, 0) = -sin(y);
    rotate_matrix(2, 2) = cos(y);
  } else if (z != 0) {
    rotate_matrix(0, 0) = cos(z);
    rotate_matrix(0, 1) = -sin(z);
    rotate_matrix(1, 0) = sin(z);
    rotate_matrix(1, 1) = cos(z);
  }
  result = rotate_matrix * cur_point;
}

void scale(float x, float y, float z, S21Matrix &cur_point, S21Matrix &result) {
  S21Matrix scale_matrix(4, 4);
  scale_matrix(0, 0) = x;
  scale_matrix(1, 1) = y;
  scale_matrix(2, 2) = z;
  scale_matrix(3, 3) = 1;

  result = scale_matrix * cur_point;
}
