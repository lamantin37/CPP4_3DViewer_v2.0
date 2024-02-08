#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <functional>
#include <iostream>
const short kDefaultSize = 0;
const short kOutOfRange = 2;
const short kInvalidArg = 3;
const double kEpsilon = 1e-07;

class S21Matrix {
 public:
  explicit S21Matrix()
      : rows_(kDefaultSize), cols_(kDefaultSize), matrix_(nullptr){};
  explicit S21Matrix(int r, int c);
  ~S21Matrix();
  S21Matrix(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other) noexcept;
  S21Matrix(S21Matrix&& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  int getRows() const { return rows_; }
  int getCols() const { return cols_; }
  double** getMatrix() const { return matrix_; }
  void setRows(int r);
  void setCols(int c);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double number) noexcept;
  bool operator==(const S21Matrix& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double number) noexcept;
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  bool EqMatrix(const S21Matrix& other) noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

 private:
  int rows_ = kDefaultSize;
  int cols_ = kDefaultSize;
  double** matrix_;
  inline void MatrixOp(std::function<void(int, int)> operation) noexcept {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        operation(i, j);
      }
    }
  }
  inline void CheckMatrix(bool expression, const char* message,
                          int type) const {
    if (expression) {
      (type == kOutOfRange) ? throw std::out_of_range(message)
                            : throw std::invalid_argument(message);
    }
  }
  inline void AllocateMatrix(int r, int c) {
    matrix_ = new double*[r];
    for (int i = 0; i < r; i++) {
      matrix_[i] = new double[c]();
    }
  }
  // static const char* err_msgs[];
};

S21Matrix operator*(const double number, const S21Matrix& other);

#endif  // CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
