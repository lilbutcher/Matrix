//
// Created by qwe on 23.02.24.
//

#ifndef CPP1_S21_MATRIXPLUS_1_S21MATRIX_H
#define CPP1_S21_MATRIXPLUS_1_S21MATRIX_H

#include <cstring>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  [[nodiscard]] double GetRows() const;
  void SetRows(int rows);
  [[nodiscard]] double GetCols() const;
  void SetCols(int cols);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix Minor(int rows, int cols);
  double AlgebraicComplement(int rows, int cols);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix &operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(double num);
  S21Matrix &operator*=(double num);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  double &operator()(int i, int j);
};

#endif  // CPP1_S21_MATRIXPLUS_1_S21MATRIX_H
