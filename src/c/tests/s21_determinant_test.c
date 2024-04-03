#include "s21_matrix_test.h"

START_TEST(test_s21_determinant_1) {
  matrix_t matrix;
  double determinant = 0;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1.0;
  matrix.matrix[0][1] = 2.0;
  matrix.matrix[0][2] = 3.0;
  matrix.matrix[1][0] = 4.0;
  matrix.matrix[1][1] = 5.0;
  matrix.matrix[1][2] = 6.0;
  matrix.matrix[2][0] = 7.0;
  matrix.matrix[2][1] = 8.0;
  matrix.matrix[2][2] = 9.0;
  //  s21_print_matrix(matrix);

  int res = s21_determinant(&matrix, &determinant);
  //  0 == OK
  ck_assert_int_eq(0, res);
  //  check determinant
  ck_assert_double_eq(0.00000, determinant);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_2) {
  matrix_t matrix;
  double determinant = 0;
  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 1.0;
  matrix.matrix[0][1] = 0.0;
  matrix.matrix[0][2] = 2.0;
  matrix.matrix[0][3] = -1.0;
  matrix.matrix[1][0] = 3.0;
  matrix.matrix[1][1] = 0.0;
  matrix.matrix[1][2] = 0.0;
  matrix.matrix[1][3] = 5.0;
  matrix.matrix[2][0] = 2.0;
  matrix.matrix[2][1] = 1.0;
  matrix.matrix[2][2] = 4.0;
  matrix.matrix[2][3] = -3.0;
  matrix.matrix[3][0] = 1.0;
  matrix.matrix[3][1] = 0.0;
  matrix.matrix[3][2] = 5.0;
  matrix.matrix[3][3] = 0.0;
  //  s21_print_matrix(matrix);

  int res = s21_determinant(&matrix, &determinant);
  //  0 == OK
  ck_assert_int_eq(0, res);
  //  check determinant
  ck_assert_double_eq(30.000000, determinant);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_3) {
  matrix_t A;
  double B, R = 1.25;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.25;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_4) {
  matrix_t A;
  double B, R = -69;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_5) {
  matrix_t A;
  double B, R = -2;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = -5;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_6) {
  matrix_t A;
  double B, R = 25;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_7) {
  matrix_t A;
  double B, R = 23;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_8) {
  matrix_t A;
  double B, R = -8;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -7;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 5;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_9) {
  matrix_t A;
  double B, R = 18;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = -5;
  A.matrix[0][3] = 8;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = -6;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = -7;
  A.matrix[2][3] = 5;
  A.matrix[3][0] = -4;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = -6;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_10) {
  matrix_t A;
  double B, R = -69.0 / 4.0;
  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[0][3] = 3.25;
  A.matrix[0][4] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[1][3] = 5.25;
  A.matrix[1][4] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;
  A.matrix[2][3] = 6.25;
  A.matrix[2][4] = 6.25;
  A.matrix[3][0] = 6.25;
  A.matrix[3][1] = 7.25;
  A.matrix[3][2] = 8.25;
  A.matrix[3][3] = 6.25;
  A.matrix[3][4] = 7.25;
  A.matrix[4][0] = 6.25;
  A.matrix[4][1] = 7.25;
  A.matrix[4][2] = 8.25;
  A.matrix[4][3] = 6;
  A.matrix[4][4] = 8.25;

  s21_determinant(&A, &B);

  ck_assert_double_eq_tol(B, R, EPS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_11) {
  matrix_t a;
  double number;
  s21_create_matrix(4, 4, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[0][3] = 13;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 6;
  a.matrix[1][3] = 16;
  a.matrix[2][0] = 7;
  a.matrix[2][1] = 8;
  a.matrix[2][2] = 90;
  a.matrix[2][3] = 19;
  a.matrix[3][0] = 1;
  a.matrix[3][1] = 7;
  a.matrix[3][2] = 7;
  a.matrix[3][3] = 17;

  s21_determinant(&a, &number);
  ck_assert_int_eq(number, 13608);
  s21_remove_matrix(&a);
}
END_TEST
// Not square matrix
START_TEST(test_s21_determinant_12) {
  matrix_t A;
  double B;
  s21_create_matrix(4, 5, &A);
  int res = s21_determinant(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST
// NULL matrix
START_TEST(test_s21_determinant_13) {
  matrix_t* B = NULL;
  double re = 0;
  int res = s21_determinant(B, &re);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_determinant_14) {
  matrix_t matrix;
  double determinant = 0;
  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 1.0;
  matrix.matrix[0][1] = 2.0;
  matrix.matrix[1][0] = 4.0;
  matrix.matrix[1][1] = 5.0;

  int res = s21_determinant(&matrix, &determinant);
  //  0 == OK
  ck_assert_int_eq(0, res);
  //  check determinant
  ck_assert_double_eq(-3.00000, determinant);

  s21_remove_matrix(&matrix);
}
END_TEST

Suite* s21_determinant_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_determinant_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_determinant_1);
  tcase_add_test(tc_core, test_s21_determinant_2);
  tcase_add_test(tc_core, test_s21_determinant_3);
  tcase_add_test(tc_core, test_s21_determinant_4);
  tcase_add_test(tc_core, test_s21_determinant_5);
  tcase_add_test(tc_core, test_s21_determinant_6);
  tcase_add_test(tc_core, test_s21_determinant_7);
  tcase_add_test(tc_core, test_s21_determinant_8);
  tcase_add_test(tc_core, test_s21_determinant_9);
  tcase_add_test(tc_core, test_s21_determinant_10);
  tcase_add_test(tc_core, test_s21_determinant_11);
  tcase_add_test(tc_core, test_s21_determinant_12);
  tcase_add_test(tc_core, test_s21_determinant_13);
  tcase_add_test(tc_core, test_s21_determinant_14);

  suite_add_tcase(s, tc_core);
  return s;
}