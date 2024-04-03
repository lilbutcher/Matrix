#include "s21_matrix_test.h"

START_TEST(test_s21_inverse_1) {
  int rows = 3;
  int cols = 3;
  matrix_t matrix;
  matrix_t result;
  matrix_t check;
  s21_create_matrix(rows, cols, &matrix);
  s21_create_matrix(rows, cols, &check);
  matrix.matrix[0][0] = 2.0;
  matrix.matrix[0][1] = 5.0;
  matrix.matrix[0][2] = 7.0;

  matrix.matrix[1][0] = 6.0;
  matrix.matrix[1][1] = 3.0;
  matrix.matrix[1][2] = 4.0;

  matrix.matrix[2][0] = 5.0;
  matrix.matrix[2][1] = -2.0;
  matrix.matrix[2][2] = -3.0;
  // s21_print_matrix(&matrix);
  check.matrix[0][0] = 1.0;
  check.matrix[0][1] = -1.0;
  check.matrix[0][2] = 1.0;
  check.matrix[1][0] = -38.0;
  check.matrix[1][1] = 41.0;
  check.matrix[1][2] = -34.0;
  check.matrix[2][0] = 27.0;
  check.matrix[2][1] = -29.0;
  check.matrix[2][2] = 24.0;
  // s21_print_matrix(&check);

  int res = s21_inverse_matrix(&matrix, &result);
  // s21_print_matrix(&result);
  //   0 == OK
  ck_assert_int_eq(0, res);
  //  check invert matrix
  res = s21_eq_matrix(&result, &check);
  //  1 == EQUAL
  ck_assert_int_eq(1, res);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_s21_inverse_2) {
  int rows = 1;
  int cols = 1;
  matrix_t matrix;
  matrix_t result;
  s21_create_matrix(rows, cols, &matrix);
  matrix.matrix[0][0] = 2.0;

  // s21_print_matrix(&check);

  int res = s21_inverse_matrix(&matrix, &result);
  // s21_print_matrix(&result);
  //   0 == OK
  ck_assert_int_eq(0, res);
  ck_assert_double_eq(result.matrix[0][0], 0.5);
  //  check invert matrix
  //  1 == EQUAL

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_3) {
  matrix_t m, B, R;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &B);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;

  int code = s21_inverse_matrix(&m, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
// Not square matrix
START_TEST(test_s21_inverse_4) {
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 4, &m);
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&m);
}
END_TEST
// NULL matrix
START_TEST(test_s21_inverse_5) {
  matrix_t* B = NULL;
  matrix_t* R = NULL;
  int res = s21_inverse_matrix(B, R);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_inverse_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_inverse_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_inverse_1);
  tcase_add_test(tc_core, test_s21_inverse_2);
  tcase_add_test(tc_core, test_s21_inverse_3);
  tcase_add_test(tc_core, test_s21_inverse_4);
  tcase_add_test(tc_core, test_s21_inverse_5);

  suite_add_tcase(s, tc_core);
  return s;
}