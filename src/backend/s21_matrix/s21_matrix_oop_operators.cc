#include "s21_matrix_oop.h"

extern const char* err_msgs[];

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix resultMatrix(*this);
  resultMatrix.SumMatrix(other);
  return resultMatrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix resultMatrix(*this);
  resultMatrix.SubMatrix(other);
  return resultMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix resultMatrix(*this);
  resultMatrix.MulMatrix(other);
  return resultMatrix;
}

S21Matrix S21Matrix::operator*(const double number) noexcept {
  S21Matrix resultMatrix(*this);
  resultMatrix.MulNumber(number);
  return resultMatrix;
}

S21Matrix operator*(const double number, const S21Matrix& other) {
  S21Matrix resultMatrix(other);
  resultMatrix.MulNumber(number);
  return resultMatrix;
}

bool S21Matrix::operator==(const S21Matrix& other) noexcept {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double number) noexcept {
  MulNumber(number);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  CheckMatrix(row >= rows_ || col >= cols_ || row < 0 || col < 0, err_msgs[3],
              kOutOfRange);
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  CheckMatrix(row >= rows_ || col >= cols_ || row < 0 || col < 0, err_msgs[3],
              kOutOfRange);
  return matrix_[row][col];
}
