#include "s21_matrix_test.h"

START_TEST(test_s21_calc_complem_1) {
  int rows = 3;
  int cols = 3;
  matrix_t matrix;
  matrix_t result;
  matrix_t check;
  s21_create_matrix(rows, cols, &matrix);
  s21_create_matrix(rows, cols, &check);
  matrix.matrix[0][0] = 1.0;
  matrix.matrix[0][1] = 2.0;
  matrix.matrix[0][2] = 3.0;

  matrix.matrix[1][0] = 0.0;
  matrix.matrix[1][1] = 4.0;
  matrix.matrix[1][2] = 2.0;

  matrix.matrix[2][0] = 5.0;
  matrix.matrix[2][1] = 2.0;
  matrix.matrix[2][2] = 1.0;
  // s21_print_matrix(&matrix);
  check.matrix[0][0] = 0.0;
  check.matrix[0][1] = 10.0;
  check.matrix[0][2] = -20.0;
  check.matrix[1][0] = 4.0;
  check.matrix[1][1] = -14.0;
  check.matrix[1][2] = 8.0;
  check.matrix[2][0] = -8.0;
  check.matrix[2][1] = -2.0;
  check.matrix[2][2] = 4.0;
  // s21_print_matrix(&check);

  int res = s21_calc_complements(&matrix, &result);
  // s21_print_matrix(&result);
  //   0 == OK
  ck_assert_int_eq(0, res);
  //  check complements matrix
  res = s21_eq_matrix(&result, &check);
  //  1 == EQUAL
  ck_assert_int_eq(1, res);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_s21_calc_complem_2) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &A);

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = 2;
  B.matrix[2][2] = 1;

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = -20;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -14;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = -8;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 4;

  int code = s21_calc_complements(&B, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complem_3) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 3;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 9;
  B.matrix[0][1] = -2;
  B.matrix[0][2] = -3;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 14;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = -7;
  B.matrix[2][1] = -18;
  B.matrix[2][2] = 17;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
// Not square matrix
START_TEST(test_s21_calc_complem_4) {
  matrix_t B, R;
  s21_create_matrix(2, 3, &B);

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;

  int code = s21_calc_complements(&B, &R);

  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_calc_complem_5) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 5;
  s21_calc_complements(&A, &R);
  B.matrix[0][0] = 1;
  // error - 2
  ck_assert_int_eq(s21_eq_matrix(&R, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
// NULL matrix
START_TEST(test_s21_calc_complem_6) {
  matrix_t* B = NULL;
  matrix_t* R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_calc_complem_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_calc_complem_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_calc_complem_1);
  tcase_add_test(tc_core, test_s21_calc_complem_2);
  tcase_add_test(tc_core, test_s21_calc_complem_3);
  tcase_add_test(tc_core, test_s21_calc_complem_4);
  tcase_add_test(tc_core, test_s21_calc_complem_5);
  tcase_add_test(tc_core, test_s21_calc_complem_6);

  suite_add_tcase(s, tc_core);
  return s;
}