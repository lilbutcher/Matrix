#ifndef SRC_S21_MATRIX_TEST_H_
#define SRC_S21_MATRIX_TEST_H_

#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "../s21_matrix.h"

Suite* s21_create_test(void);
Suite* s21_remove_test(void);
Suite* s21_eq_matrix_test(void);
Suite* s21_sum_test(void);
Suite* s21_sub_test(void);
Suite* s21_mult_number_test(void);
Suite* s21_mult_matrix_test(void);
Suite* s21_transpose_test(void);
Suite* s21_calc_complem_test(void);
Suite* s21_determinant_test(void);
Suite* s21_inverse_test(void);

void run_test(void);
void run_testcase(Suite* testcase);

#endif  //  SRC_S21_MATRIX_TEST_H_