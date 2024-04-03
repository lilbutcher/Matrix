#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  s21_errors error = OK;
  if (rows <= 0 || columns <= 0) {
    error = ERROR;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));

    if (!result->matrix) {
      error = MEMORY_ERROR;
      return error;
    }

    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
        }
        free(result->matrix);
        return MEMORY_ERROR;
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int check = 1;
  if (check_matrix(A) && check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
            return FAILURE;
          }
        }
      }
    } else {
      check = FAILURE;
    }
  } else {
    check = FAILURE;
  }
  return check;
}