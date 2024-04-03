#include "s21_matrix_test.h"

START_TEST(test_s21_eq_matrix_1) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, cols, &matrix1);
  s21_create_matrix(rows, cols, &matrix2);
  int res = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  // 1 - equal
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_s21_eq_matrix_2) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, cols, &matrix1);
  matrix1.matrix[1][1] = 0.001;
  s21_create_matrix(rows, cols, &matrix2);
  int res = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  // 0 - not equal
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(test_s21_eq_matrix_3) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, cols, &matrix1);
  // error matrix
  matrix1.columns = 0;
  s21_create_matrix(rows, cols, &matrix2);
  int res = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  // 0 - not eq
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(test_s21_eq_matrix_4) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, cols, &matrix1);
  // more then epslion
  matrix1.matrix[1][1] = 0.0000001;
  s21_create_matrix(rows, cols, &matrix2);
  int res = s21_eq_matrix(&matrix1, &matrix2);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  // 1 - equal
  ck_assert_int_eq(1, res);
}
END_TEST

Suite* s21_eq_matrix_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_eq_matrix_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_eq_matrix_1);
  tcase_add_test(tc_core, test_s21_eq_matrix_2);
  tcase_add_test(tc_core, test_s21_eq_matrix_3);
  tcase_add_test(tc_core, test_s21_eq_matrix_4);

  suite_add_tcase(s, tc_core);
  return s;
}