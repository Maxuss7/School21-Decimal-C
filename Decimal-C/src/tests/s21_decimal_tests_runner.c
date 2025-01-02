#include <stdlib.h>

#include "s21_decimal_tests.h"

int main() {
  int failed_tests = 0;

  Suite *s = get_suite_s21_from_int_to_decimal();
  SRunner *sr = srunner_create(s);

  // arithmetic
  srunner_add_suite(sr, get_suite_s21_add());
  srunner_add_suite(sr, get_suite_s21_sub());
  srunner_add_suite(sr, get_suite_s21_mul());
  srunner_add_suite(sr, get_suite_s21_div());

  // convert
  // srunner_add_suite(sr, get_suite_s21_from_int_to_decimal());
  srunner_add_suite(sr, get_suite_s21_from_float_to_decimal());
  srunner_add_suite(sr, get_suite_s21_from_decimal_to_int());
  srunner_add_suite(sr, get_suite_s21_from_decimal_to_float());

  // comparison
  srunner_add_suite(sr, get_suite_s21_is_less());
  srunner_add_suite(sr, get_suite_s21_is_less_or_equal());
  srunner_add_suite(sr, get_suite_s21_is_greater());
  srunner_add_suite(sr, get_suite_s21_is_greater_or_equal());
  srunner_add_suite(sr, get_suite_s21_is_equal());
  srunner_add_suite(sr, get_suite_s21_is_not_equal());
  // srunner_add_suite(sr, s21_test_comparison()); // additional comparison
  // tests

  // others
  srunner_add_suite(sr, get_suite_s21_floor());
  srunner_add_suite(sr, get_suite_s21_round());
  srunner_add_suite(sr, get_suite_s21_truncate());
  srunner_add_suite(sr, get_suite_s21_negate());

  srunner_add_suite(sr, s21_test_comparison());  // additional comparison tests

  // srunner_set_fork_status(sr, CK_NOFORK); // for valgrind chechs
  srunner_run_all(sr, CK_VERBOSE);
  failed_tests = srunner_ntests_failed(sr);
  printf("=== FAILED TESTS: %d ===\n", failed_tests);

  srunner_free(sr);
  return (failed_tests == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}