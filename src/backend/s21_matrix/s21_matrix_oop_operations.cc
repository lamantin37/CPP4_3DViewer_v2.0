#include "s21_matrix_oop.h"

extern const char* err_msgs[];

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  bool isEqual = true;
  MatrixOp([&](int i, int j) {
    if (fabs(matrix_[i][j] - other.matrix_[i][j]) > kEpsilon) {
      isEqual = false;
    }
  });
  return isEqual;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  CheckMatrix(rows_ != other.rows_ || cols_ != other.cols_, err_msgs[0],
              kOutOfRange);
  MatrixOp([&](int i, int j) { matrix_[i][j] += other.matrix_[i][j]; });
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  CheckMatrix(rows_ != other.rows_ || cols_ != other.cols_, err_msgs[0],
              kOutOfRange);
  MatrixOp([&](int i, int j) { matrix_[i][j] -= other.matrix_[i][j]; });
}

void S21Matrix::MulNumber(const double num) noexcept {
  MatrixOp([&](int i, int j) { matrix_[i][j] *= num; });
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  CheckMatrix(cols_ != other.rows_, err_msgs[0], kOutOfRange);
  S21Matrix resultMatrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        resultMatrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = resultMatrix;
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix TransposedMatrix(cols_, rows_);
  for (int i = 0; i < TransposedMatrix.getRows(); i++) {
    for (int j = 0; j < TransposedMatrix.getCols(); j++) {
      TransposedMatrix.getMatrix()[i][j] = matrix_[j][i];
    }
  }
  return TransposedMatrix;
}

double S21Matrix::Determinant() {
  CheckMatrix(cols_ != rows_, err_msgs[0], kOutOfRange);
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    int sign = 1;
    for (int i = 0; i < rows_; i++) {
      S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
      for (int row = 1; row < rows_; row++) {
        int col_offset = 0;
        for (int col = 0; col < cols_; col++) {
          if (col != i) {
            minor_matrix.matrix_[row - 1][col_offset] = matrix_[row][col];
            col_offset++;
          }
        }
      }
      result += sign * matrix_[0][i] * minor_matrix.Determinant();
      sign = -sign;
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  CheckMatrix(rows_ != cols_, err_msgs[1], kOutOfRange);
  S21Matrix complements(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
      int row_offset = 0;
      for (int row = 0; row < rows_; row++) {
        if (row != i) {
          int col_offset = 0;
          for (int col = 0; col < cols_; col++) {
            if (col != j) {
              minor_matrix.matrix_[row_offset][col_offset] = matrix_[row][col];
              col_offset++;
            }
          }
          row_offset++;
        }
      }
      complements.matrix_[i][j] = ((i + j) % 2 == 0) ? 1 : -1;
      complements.matrix_[i][j] *= minor_matrix.Determinant();
    }
  }
  return complements;
}

S21Matrix S21Matrix::InverseMatrix() {
  CheckMatrix(rows_ != cols_, err_msgs[1], kOutOfRange);
  double determinant = Determinant();
  CheckMatrix(determinant == 0, err_msgs[2], kOutOfRange);
  S21Matrix complements = CalcComplements();
  S21Matrix inverse(rows_, cols_);
  MatrixOp([&](int i, int j) {
    inverse.matrix_[j][i] = complements.matrix_[i][j] / determinant;
  });
  return inverse;
}
