#include "s21_matrix_test.h"

START_TEST(test_s21_remove_1) {
  int rows = 10;
  int columns = 10;
  matrix_t matrix = {0};
  int code = s21_create_matrix(rows, columns, &matrix);
  if (code == 0) {
    s21_remove_matrix(&matrix);
    ck_assert_ptr_null(matrix.matrix);
    ck_assert_int_eq(matrix.rows, 0);
    ck_assert_int_eq(matrix.columns, 0);
  }
}
END_TEST

Suite* s21_remove_test(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("\033[97m\033[106ms21_remove_test\033[0m");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_remove_1);

  suite_add_tcase(s, tc_core);
  return s;
}