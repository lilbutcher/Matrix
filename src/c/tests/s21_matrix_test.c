#include "s21_matrix_test.h"

void run_test(void) {
  Suite *list_cases[] = {
      s21_create_test(),      s21_remove_test(),    s21_eq_matrix_test(),
      s21_sum_test(),         s21_sub_test(),       s21_mult_number_test(),
      s21_mult_matrix_test(), s21_transpose_test(), s21_calc_complem_test(),
      s21_determinant_test(), s21_inverse_test(),   NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_test();
  return 0;
}