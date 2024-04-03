#include "s21_matrix.h"

int check_matrix(matrix_t *A) {
  int check = 1;
  if (A == NULL) {
    check = 0;
  } else if (A->matrix == NULL) {
    check = 0;
  } else if (A->rows < 1 || A->columns < 1) {
    check = 0;
  }
  return check;
}

int minor_matrix(int row, int column, matrix_t A, matrix_t *result) {
  s21_errors error = OK;
  if (A.rows >= 2 && result->rows == A.rows - 1 && row >= 0 && row < A.rows &&
      column >= 0 && column < A.columns) {
    int cut_row = 0;
    int cut_col = 0;
    for (int i = 0; i < A.rows - 1; i++) {
      if (i == row) {
        cut_row = 1;
      }
      cut_col = 0;
      for (int j = 0; j < A.columns - 1; j++) {
        if (j == column) {
          cut_col = 1;
        }
        result->matrix[i][j] = A.matrix[i + cut_row][j + cut_col];
      }
    }
  } else {
    error = ERROR;
  }
  return error;
}