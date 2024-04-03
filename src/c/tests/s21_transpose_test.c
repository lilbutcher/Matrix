#include "s21_matrix_test.h"

START_TEST(test_s21_transpose_1) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 2.25;
  B.matrix[0][0] = 2.25;

  s21_transpose(&A, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_s21_transpose_2) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_transpose(&A, &R);

  B.matrix[0][0] = 0.25;
  B.matrix[1][0] = 1.25;
  B.matrix[2][0] = 2.25;
  B.matrix[0][1] = 3.25;
  B.matrix[1][1] = 4.25;
  B.matrix[2][1] = 5.25;
  B.matrix[0][2] = 6.25;
  B.matrix[1][2] = 7.25;
  B.matrix[2][2] = 8.25;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
// Incorrect matrix
START_TEST(test_s21_transpose_3) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.columns = -1;

  int ret = s21_transpose(&A, &B);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
// NULL matrix
START_TEST(test_s21_transpose_4) {
  matrix_t* B = NULL;
  matrix_t* R = NULL;
  int res = s21_transpose(B, R);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_transpose_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_transpose_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_transpose_1);
  tcase_add_test(tc_core, test_s21_transpose_2);
  tcase_add_test(tc_core, test_s21_transpose_3);
  tcase_add_test(tc_core, test_s21_transpose_4);

  suite_add_tcase(s, tc_core);
  return s;
}