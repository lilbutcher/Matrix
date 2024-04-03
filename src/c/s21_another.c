#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A)) {
    error = s21_create_matrix(A->columns, A->rows, result);
    if (error == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  s21_errors error = OK;
  if (check_matrix(A)) {
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else if (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] -
                  A->matrix[0][1] * A->matrix[1][0];
      } else {
        matrix_t tmp = {0};
        double res;
        double summa = 0.0;
        s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);

        for (int i = 0; i < A->columns; i++) {
          res = 0.0;
          minor_matrix(0, i, *A, &tmp);
          s21_determinant(&tmp, &res);
          if (i % 2) {
            summa -= res * A->matrix[0][i];
          } else {
            summa += res * A->matrix[0][i];
          }
        }
        s21_remove_matrix(&tmp);
        *result = summa;
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A)) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      if (A->rows > 1) {
        matrix_t tmp = {0};
        double determinant = 0.0;
        s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
        for (int i = 0; i < A->rows; ++i) {
          for (int j = 0; j < A->columns; ++j) {
            determinant = 0.0;
            minor_matrix(i, j, *A, &tmp);
            s21_determinant(&tmp, &determinant);
            if ((i + j) % 2) {
              result->matrix[i][j] = determinant * -1.0;
            } else {
              result->matrix[i][j] = determinant;
            }
          }
        }
        s21_remove_matrix(&tmp);
      } else {
        error = CALC_ERROR;
      }
    } else {
      error = CALC_ERROR;
    }
  } else {
    error = ERROR;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  s21_errors error = OK;
  if (check_matrix(A)) {
    double det = 0.0;
    s21_determinant(A, &det);
    if (det != 0) {
      if (A->rows > 1) {
        s21_create_matrix(A->rows, A->columns, result);
        matrix_t complements;
        matrix_t transpose;
        s21_calc_complements(A, &complements);
        s21_transpose(&complements, &transpose);
        s21_remove_matrix(&complements);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = -1.0 * transpose.matrix[i][j];
          }
        }
      } else if (A->rows == 1) {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        error = CALC_ERROR;
      }
    } else {
      error = CALC_ERROR;
    }

  } else {
    error = ERROR;
  }
  return error;
}
