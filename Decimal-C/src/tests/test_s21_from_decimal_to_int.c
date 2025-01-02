#include "s21_decimal_tests.h"

// Note: used INT_MIN and INT_MAN from <limits.h>
// #define DEBUG_TEST_S21_FROM_DECIMAL_TO_INT

void test_proc_s21_from_decimal_to_int(const s21_decimal *psrc,
                                       const int *ptdst, const int *ptres);

// 1. Tests with correct parameters (return res = 0)

START_TEST(s21_from_decimal_to_int_t101) {  // s21_decimal src = +0
  s21_decimal src = {{0, 0, 0, 0}};
  int tdst = 0;
  int tres = 0;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t102) {  // s21_decimal  src = -0
  s21_decimal src = {{0, 0, 0, 0x80000000}};
  int tdst = 0;
  int tres = 0;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t103) {  // src > 0 (scale = 5)
  s21_decimal src = {{1234567890, 0, 0, 0x00050000}};
  int tdst = 12345;
  int tres = 0;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t104) {  // src < 0 (scale = 5)
  s21_decimal src = {{1234567890, 0, 0, 0x80050000}};
  int tdst = -12345;
  int tres = 0;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t105) {  // (int)src = INT_MAX (scale = 0)
  s21_decimal src = {{INT_MAX, 0, 0, 0x00000000}};
  int tdst = INT_MAX;
  int tres = 0;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t106) {  // (int)src = INT_MIN (scale = 0)
  s21_decimal src = {{(unsigned)abs(INT_MIN + 1) + 1, 0, 0, 0x80000000}};
  int tdst = INT_MIN;
  int tres = 0;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

// 2. Tests with incorrect parameters  (return res != 0)

START_TEST(s21_from_decimal_to_int_t201) {  // test int *dst == NULL
  s21_decimal src = {{1234567890, 0, 0, 0x00050000}};
  int *pdst = NULL;
  int tres = 1;

  int res = s21_from_decimal_to_int(src, pdst);
  ck_assert_int_eq((int)res, (int)(tres));
}
END_TEST

START_TEST(s21_from_decimal_to_int_t202) {  // src > INT_MAX (scale = 0)
  s21_decimal src = {{INT_MAX, 1, 1, 0x00000000}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t203) {  // (src > INT_MAX (scale = 0)
  s21_decimal src = {{INT_MAX, 1, 0, 0x00000000}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t204) {  // (src < INT_MIN (scale = 3)
  s21_decimal src = {{(unsigned)abs(INT_MIN + 1) + 1, 0, 1, 0x80030000}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t205) {  // src < INT_MIN (scale = 1)
  s21_decimal src = {{(unsigned)abs(INT_MIN + 1) + 1, 123, 0, 0x80010000}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t206) {  // src incorrect (1 in unused bits)
  s21_decimal src = {{12345, 0, 0, 0x00000011}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t207) {  // src incorrect (1 in unused bits)
  s21_decimal src = {{12345, 0, 0, 0x80000011}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t208) {  // (src > INT_MAX (scale = 0)
  s21_decimal src = {{(unsigned)INT_MAX + 123, 0, 0, 0x00000000}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_int_t209) {  // (src < INT_MIN (scale = 0)
  s21_decimal src = {{(unsigned)abs(INT_MIN + 1) + 1 + 123, 0, 0, 0x80000000}};
  int tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_int(&src, &tdst, &tres);
}
END_TEST

// ==============================================================
// Suite setup
// ==============================================================
Suite *get_suite_s21_from_decimal_to_int(void) {
  Suite *s = suite_create("s21_from_decimal_to_int_suite");

  TCase *tc = tcase_create("tc");
  tcase_add_test(tc, s21_from_decimal_to_int_t101);
  tcase_add_test(tc, s21_from_decimal_to_int_t102);
  tcase_add_test(tc, s21_from_decimal_to_int_t103);
  tcase_add_test(tc, s21_from_decimal_to_int_t104);
  tcase_add_test(tc, s21_from_decimal_to_int_t105);
  tcase_add_test(tc, s21_from_decimal_to_int_t106);
  tcase_add_test(tc, s21_from_decimal_to_int_t201);
  tcase_add_test(tc, s21_from_decimal_to_int_t202);
  tcase_add_test(tc, s21_from_decimal_to_int_t203);
  tcase_add_test(tc, s21_from_decimal_to_int_t204);
  tcase_add_test(tc, s21_from_decimal_to_int_t205);
  tcase_add_test(tc, s21_from_decimal_to_int_t206);
  tcase_add_test(tc, s21_from_decimal_to_int_t207);
  tcase_add_test(tc, s21_from_decimal_to_int_t208);
  tcase_add_test(tc, s21_from_decimal_to_int_t209);
  suite_add_tcase(s, tc);

  return s;
}

// common part of the tests for s21_from_decimal_to_int func is placed to the
// proc
void test_proc_s21_from_decimal_to_int(const s21_decimal *psrc,
                                       const int *ptdst, const int *ptres) {
#ifdef DEBUG_TEST_S21_FROM_DECIMAL_TO_INT
  printf("DEBUG:  psrc->bits'[3] [2] [1] [0]': '%X %X %X %X'  \n",
         psrc->bits[3], psrc->bits[2], psrc->bits[1], psrc->bits[0]);
  fflush(NULL);
#endif

  int dst = INT_MAX / 128;

  int res = s21_from_decimal_to_int(*psrc, &dst);
  ck_assert_int_eq((int)res, (int)(*ptres));
  if (res == 0) {
    ck_assert_int_eq((int)dst, (int)(*ptdst));
  } else {
    ck_assert_int_eq((int)dst, (int)(INT_MAX / 128));
  }

#ifdef DEBUG_TEST_S21_FROM_DECIMAL_TO_INT
  fflush(NULL);
#endif
}