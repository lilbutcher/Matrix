#include "s21_matrix_test.h"

START_TEST(test_s21_create_1) {
  int rows = 0;
  int cols = 1;
  matrix_t matrix;
  int res = s21_create_matrix(rows, cols, &matrix);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_s21_create_2) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix;
  int res = s21_create_matrix(rows, cols, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(test_s21_create_3) {
  int rows = 10;
  int columns = 10;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);

  if (matrix.matrix) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        ck_assert_double_eq_tol(matrix.matrix[i][j], 0, 1e-6);
      }
    }
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);
    ck_assert_int_eq(code, 0);
  } /*else {
    ck_assert_int_eq(code, 1);
  }*/

  if (code == 0) s21_remove_matrix(&matrix);
}
END_TEST
// Incorrect matrix
START_TEST(test_s21_create_4) {
  int rows = -10;
  int columns = 10;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(code, 1);

  if (code == 0) s21_remove_matrix(&matrix);
}
END_TEST

Suite* s21_create_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_create_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_create_1);
  tcase_add_test(tc_core, test_s21_create_2);
  tcase_add_test(tc_core, test_s21_create_3);
  tcase_add_test(tc_core, test_s21_create_4);

  suite_add_tcase(s, tc_core);
  return s;
}