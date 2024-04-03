//
// Created by qwe on 23.02.24.
//

#include "S21Matrix.h"

// A basic constructor.
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// Parametrized constructor with number of rows and columns.
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::invalid_argument("Incorrect argument values");
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

// Copy constructor.
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Move constructor.
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Destructor.
S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

double S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::invalid_argument("Incorrect argument value");
  }

  double **newMatrix = new double *[rows];
  for (int i = 0; i < rows; i++) {
    newMatrix[i] = new double[cols_];
  }

  int minRows = std::min(rows, rows_);
  for (int i = 0; i < minRows; i++) {
    for (int j = 0; j < cols_; j++) {
      newMatrix[i][j] = matrix_[i][j];
    }
  }

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  matrix_ = newMatrix;
  rows_ = rows;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::invalid_argument("Incorrect argument value");
  }

  double **newMatrix = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    newMatrix[i] = new double[cols];
  }

  int minCols = std::min(cols, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < minCols; j++) {
      newMatrix[i][j] = matrix_[i][j];
    }
  }

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  matrix_ = newMatrix;
  cols_ = cols;
}

double S21Matrix::GetCols() const { return cols_; }

// Checks matrices for equality with each other.
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  const double epsilon = 1e-7;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > epsilon) {
        return false;
      }
    }
  }

  return true;
}

// Adds the second matrix to the current one
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Subtracts another matrix from the current one
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Creates a new transposed matrix from the current one and returns it.
void S21Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

// Calculates and returns the determinant of the current matrix.
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double summa = 0;
  S21Matrix temp(rows_ - 1, cols_ - 1);

  for (int i = 0; i < rows_; i++) {
    for (int j = 1; j < cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        if (k < i) {
          temp.matrix_[j - 1][k] = matrix_[j][k];
        } else if (k > i) {
          temp.matrix_[j - 1][k - 1] = matrix_[j][k];
        }
      }
    }

    double sign = (i % 2 == 0) ? 1 : -1;
    summa += sign * matrix_[0][i] * temp.Determinant();
  }

  return summa;
}

// Multiplies the current matrix by the second matrix.
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Number of columns in the first matrix is not equal to the number of "
        "rows in the second matrix");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  // Copy the result matrix to the current matrix
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = result.matrix_[i][j];
    }
  }

  this->SetRows(rows_);
  this->SetCols(other.cols_);
}

// Creates a new transposed matrix from the current one and returns it.
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }

  return result;
}

// Creates a minor matrix
S21Matrix S21Matrix::Minor(int rows, int cols) {
  if (rows < 0 || rows >= rows_ || cols < 0 || cols >= cols_) {
    throw std::out_of_range("Invalid row or column index");
  }

  S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
  int minorRows = 0, minorCols;

  for (int i = 0; i < rows_; i++) {
    if (i == rows) {
      continue;
    }
    minorCols = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == cols) {
        continue;
      }

      minorMatrix.matrix_[minorRows][minorCols] = matrix_[i][j];
      minorCols++;
    }

    minorRows++;
  }

  return minorMatrix;
}

// Function for finding the algebraic complement of a matrix
double S21Matrix::AlgebraicComplement(int rows, int cols) {
  if ((rows + cols) % 2 == 0) {
    return Minor(rows, cols).Determinant();
  } else {
    return -Minor(rows, cols).Determinant();
  }
}

// Calculates the algebraic addition matrix of the current one and returns it.
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  S21Matrix comMatrix(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      comMatrix.matrix_[i][j] = AlgebraicComplement(i, j);
    }
  }

  return comMatrix;
}

// Assignment of values from one matrix to another one.
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
    }

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

// Calculates and returns the inverse matrix.
S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument(
        "Determinant is zero, inverse matrix does not exist");
  }

  S21Matrix adjMatrix = CalcComplements().Transpose();

  S21Matrix invMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      invMatrix.matrix_[i][j] = adjMatrix.matrix_[i][j] / det;
    }
  }

  return invMatrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix result(rows_, cols_);
  result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result = *this;
  result.MulMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range");
  }

  return matrix_[i][j];
}
