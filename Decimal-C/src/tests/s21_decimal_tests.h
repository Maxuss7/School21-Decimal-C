#ifndef SRC_S21_DECIMAL_TESTS_H
#define SRC_S21_DECIMAL_TESTS_H

#include <check.h>
#include <limits.h>
#include <stdlib.h>

#include "../s21_decimal.h"

// arithmetic
Suite *get_suite_s21_add(void);
Suite *get_suite_s21_sub(void);
Suite *get_suite_s21_mul(void);
Suite *get_suite_s21_div(void);

// convert
Suite *get_suite_s21_from_int_to_decimal(void);
Suite *get_suite_s21_from_float_to_decimal(void);
Suite *get_suite_s21_from_decimal_to_int(void);
Suite *get_suite_s21_from_decimal_to_float(void);

// comparison
Suite *get_suite_s21_is_less(void);
Suite *get_suite_s21_is_less_or_equal(void);
Suite *get_suite_s21_is_greater(void);
Suite *get_suite_s21_is_greater_or_equal(void);
Suite *get_suite_s21_is_equal(void);
Suite *get_suite_s21_is_not_equal(void);

Suite *s21_test_comparison(void);  // additional comparison test

// others
Suite *get_suite_s21_floor(void);
Suite *get_suite_s21_round(void);
Suite *get_suite_s21_truncate(void);
Suite *get_suite_s21_negate(void);

#endif