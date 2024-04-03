#include "s21_matrix_test.h"

START_TEST(test_mult_number_1) {
  matrix_t A, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 0.25;

  R2.matrix[0][0] = -1;

  s21_mult_number(&A, -4, &R);

  ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t A, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;
  R2.matrix[2][0] = 25;
  R2.matrix[2][1] = 29;
  R2.matrix[2][2] = 33;

  s21_mult_number(&A, 4, &R);

  ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], EPS);
  ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], EPS);
  ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], EPS);
  ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], EPS);
  ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], EPS);
  ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], EPS);
  ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], EPS);
  ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], EPS);
  ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST
// NULL matrix
START_TEST(test_mult_number_3) {
  matrix_t* B = NULL;
  double num = 0;
  matrix_t* R = NULL;
  int res = s21_mult_number(B, num, R);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_mult_number_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_mult_number_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_mult_number_1);
  tcase_add_test(tc_core, test_mult_number_2);
  tcase_add_test(tc_core, test_mult_number_3);

  suite_add_tcase(s, tc_core);
  return s;
}