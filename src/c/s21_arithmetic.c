#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A) && check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A) && check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A)) {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A) && check_matrix(B)) {
    if (A->columns == B->rows) {
      error = s21_create_matrix(A->rows, B->columns, result);
      if (error == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = ERROR;
  }
  return error;
}