#include "s21_matrix_test.h"

START_TEST(test_s21_sum_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 2.25;
  B.matrix[0][0] = 3.25;

  R2.matrix[0][0] = 5.5;

  s21_sum_matrix(&A, &B, &R);

  ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(test_s21_sum_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 1.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 9.65;
  B.matrix[0][1] = 9.65;
  B.matrix[0][2] = 7.65;
  B.matrix[1][0] = 6.65;
  B.matrix[1][1] = 5.65;
  B.matrix[1][2] = 4.65;
  B.matrix[2][0] = 3.65;
  B.matrix[2][1] = 2.65;
  B.matrix[2][2] = 1.65;

  R2.matrix[0][0] = 10.9;
  R2.matrix[0][1] = 10.9;
  R2.matrix[0][2] = 9.9;
  R2.matrix[1][0] = 9.9;
  R2.matrix[1][1] = 9.9;
  R2.matrix[1][2] = 9.9;
  R2.matrix[2][0] = 9.9;
  R2.matrix[2][1] = 9.9;
  R2.matrix[2][2] = 9.9;

  s21_sum_matrix(&A, &B, &R);

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
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST
// Incorrect matrix
START_TEST(test_s21_sum_3) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.05;

  int res = s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(res, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
// NULL matrix
START_TEST(test_s21_sum_4) {
  matrix_t* A = NULL;
  matrix_t* B = NULL;
  matrix_t* R = NULL;
  int res = s21_sum_matrix(A, B, R);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_sum_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_sum_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_sum_1);
  tcase_add_test(tc_core, test_s21_sum_2);
  tcase_add_test(tc_core, test_s21_sum_3);
  tcase_add_test(tc_core, test_s21_sum_4);

  suite_add_tcase(s, tc_core);
  return s;
}