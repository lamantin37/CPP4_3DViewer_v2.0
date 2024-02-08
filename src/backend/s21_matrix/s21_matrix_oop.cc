#include "s21_matrix_oop.h"

const char* err_msgs[] = {"Error: Matrix have different dimensions",
                          "Error: Matrix is not square",
                          "Error: determinant = 0",
                          "Error: out of range",
                          "Error: invalid matrix",
                          "Invalid number of rows",
                          "Invalid number of cols"};

S21Matrix::S21Matrix(int r, int c) : rows_(r), cols_(c) {
  CheckMatrix(rows_ < 1 || cols_ < 1, err_msgs[4], kOutOfRange);
  AllocateMatrix(rows_, cols_);
  // std::cout << "Created" << std::endl;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  // std::cout << "Destroyed" << std::endl;
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CheckMatrix(rows_ != other.rows_ || cols_ != other.cols_, err_msgs[0],
              kOutOfRange);
  AllocateMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
  }
  // std::cout << "Copied" << std::endl;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    cols_ = other.cols_;
    rows_ = other.rows_;
    AllocateMatrix(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
    }
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  // std::cout << "Moved" << std::endl;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

void S21Matrix::setRows(int r) {
  CheckMatrix(r < 0, err_msgs[5], kInvalidArg);
  double** newMatrix = new double*[r];
  for (int i = 0; i < r; ++i) {
    newMatrix[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      newMatrix[i][j] = (i < rows_) ? matrix_[i][j] : 0.0;
    }
  }
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = newMatrix;
  rows_ = r;
}

void S21Matrix::setCols(int c) {
  CheckMatrix(c < 0, err_msgs[6], kInvalidArg);
  for (int i = 0; i < rows_; ++i) {
    double* newRow = new double[c];
    for (int j = 0; j < c; ++j) {
      newRow[j] = (j < cols_) ? matrix_[i][j] : 0.0;
    }
    delete[] matrix_[i];
    matrix_[i] = newRow;
  }
  cols_ = c;
}
