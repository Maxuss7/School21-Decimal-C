#include "s21_decimal_tests.h"

// Note: used INT_MIN and INT_MAN from <limits.h>
// #define DEBUG_TEST_S21_FROM_INT_TO_DECIMAL

void test_proc_s21_from_int_to_decimal(const int *psrc,
                                       const s21_decimal *ptdst,
                                       const int *ptres);

// 1. Tests with correct parameters (return res = 0)

START_TEST(s21_from_int_to_decimal_t101) {  // test src = 0
  int src = 0;
  s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 0;
  test_proc_s21_from_int_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_int_to_decimal_t102) {  // test src > 0
  int src = 12345;
  s21_decimal tdst = {{12345, 0, 0, 0}};
  int tres = 0;
  test_proc_s21_from_int_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_int_to_decimal_t103) {  // test src < 0
  int src = -12345;
  s21_decimal tdst = {{12345, 0, 0, 0x80000000}};
  int tres = 0;
  test_proc_s21_from_int_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_int_to_decimal_t104) {  // test src = INT_MAX
  int src = INT_MAX;                        // +2 147 483 647
  s21_decimal tdst = {{INT_MAX, 0, 0, 0}};
  int tres = 0;
  test_proc_s21_from_int_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_int_to_decimal_t105) {  // test src = INT_MIN
  int src = INT_MIN;                        // −2 147 483 648
  s21_decimal tdst = {{(unsigned int)(INT_MIN), 0, 0, 0x80000000}};
  int tres = 0;
  test_proc_s21_from_int_to_decimal(&src, &tdst, &tres);
}
END_TEST

// 2. Tests with incorrect parameters (return res != 0)

START_TEST(s21_from_int_to_decimal_t201) {  // test s21_decimal dst == NULL
  int src = 12345;
  // s21_decimal tdst = {{12345, 0, 0, 0}};
  int tres = 1;

  // s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal *pdst = NULL;

  int res = s21_from_int_to_decimal(src, pdst);
  ck_assert_int_eq((int)res, (int)(tres));

  // ck_assert_int_eq((int)pdst->bits[0], (int)tdst.bits[0]);
  // ck_assert_int_eq((int)pdst->bits[1], (int)tdst.bits[1]);
  // ck_assert_int_eq((int)pdst->bits[2], (int)tdst.bits[2]);
  // ck_assert_int_eq((int)pdst->bits[3], (int)tdst.bits[3]);

  // ck_assert_mem_eq(&dst, &tdst, sizeof(s21_decimal));
}
END_TEST

// ==============================================================
// Suite setup
// ==============================================================
Suite *get_suite_s21_from_int_to_decimal(void) {
  Suite *s = suite_create("s21_from_int_to_decimal_suite");

  TCase *tc = tcase_create("tc");
  tcase_add_test(tc, s21_from_int_to_decimal_t101);
  tcase_add_test(tc, s21_from_int_to_decimal_t102);
  tcase_add_test(tc, s21_from_int_to_decimal_t103);
  tcase_add_test(tc, s21_from_int_to_decimal_t104);
  tcase_add_test(tc, s21_from_int_to_decimal_t105);
  tcase_add_test(tc, s21_from_int_to_decimal_t201);
  suite_add_tcase(s, tc);

  return s;
}

// common part of the tests for s21_from_int_to_decimal func is placed to the
// proc
void test_proc_s21_from_int_to_decimal(const int *psrc,
                                       const s21_decimal *ptdst,
                                       const int *ptres) {
#ifdef DEBUG_TEST_S21_FROM_INT_TO_DECIMAL
  printf("DEBUG: src = %d, (int)ptdst->bits[0] = %u \n", *psrc,
         (int)ptdst->bits[0]);
  fflush(NULL);
#endif

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};

  int res = s21_from_int_to_decimal(*psrc, &dst);
  ck_assert_int_eq((int)res, (int)(*ptres));

  ck_assert_int_eq((int)dst.bits[0], (int)ptdst->bits[0]);
  ck_assert_int_eq((int)dst.bits[1], (int)ptdst->bits[1]);
  ck_assert_int_eq((int)dst.bits[2], (int)ptdst->bits[2]);
  ck_assert_int_eq((int)dst.bits[3], (int)ptdst->bits[3]);

  // ck_assert_mem_eq(&dst, ptdst, sizeof(s21_decimal));

#ifdef DEBUG_TEST_S21_FROM_INT_TO_DECIMAL
  fflush(NULL);
#endif
}