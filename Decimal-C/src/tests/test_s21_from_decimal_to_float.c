#include "s21_decimal_tests.h"

// Note: used INT_MIN and INT_MAN from <limits.h>
// #define DEBUG_TEST_S21_FROM_DECIMAL_TO_FLOAT

void test_proc_s21_from_decimal_to_float(const s21_decimal *psrc,
                                         const float *ptdst, const int *ptres);

// 1. Tests with correct parameters (return res = 0)

START_TEST(s21_from_decimal_to_float_t101) {  // s21_decimal src = +0
  s21_decimal src = {{0, 0, 0, 0}};
  float tdst = 0;
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_float_t102) {  // s21_decimal  src = -0
  s21_decimal src = {{0, 0, 0, 0x80000000}};
  float tdst = 0;
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_float_t103) {  // src > 0 (scale = 5)
  s21_decimal src = {{1234567890, 0, 0, 0x00050000}};
  float tdst = 12345.67890;
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_float_t104) {  // src < 0 (scale = 5)
  s21_decimal src = {{1234567890, 0, 0, 0x80050000}};
  float tdst = -12345.67890;
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_float_t105) {  // MAX_MANTISSA (scale = 28)
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  float tdst = 7.9228162514264337593543950335;
  // MAX_MANTISSA: 79228162514264337593543950335
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_float_t106) {  // -MAX_MANTISSA (scale = 0)
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  float tdst = -1 * (float)(pow(2, 96) - 1);
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_decimal_to_float_t107) {  // src = 1/10^28
  s21_decimal src = {{1, 0, 0, 0x001C0000}};
  float tdst = (float)(pow(10, -28));
  int tres = 0;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

// 2. Tests with incorrect parameters  (return res != 0)

START_TEST(s21_from_decimal_to_float_t201) {  // test float *dst == NULL
  s21_decimal src = {{1234567890, 0, 0, 0x00050000}};
  float *pdst = NULL;
  int tres = 1;

  int res = s21_from_decimal_to_float(src, pdst);
  ck_assert_int_eq((int)res, (int)(tres));
}
END_TEST

START_TEST(
    s21_from_decimal_to_float_t202) {  // src incorrect (1 in unused bits)
  s21_decimal src = {{12345, 0, 0, 0x00000011}};
  float tdst = 0;  // n/a (keep initial int dst value)
  int tres = 1;
  test_proc_s21_from_decimal_to_float(&src, &tdst, &tres);
}
END_TEST

// ==============================================================
// Suite setup
// ==============================================================
Suite *get_suite_s21_from_decimal_to_float(void) {
  Suite *s = suite_create("s21_from_decimal_to_float_suite");

  TCase *tc = tcase_create("tc");
  tcase_add_test(tc, s21_from_decimal_to_float_t101);
  tcase_add_test(tc, s21_from_decimal_to_float_t102);
  tcase_add_test(tc, s21_from_decimal_to_float_t103);
  tcase_add_test(tc, s21_from_decimal_to_float_t104);
  tcase_add_test(tc, s21_from_decimal_to_float_t105);
  tcase_add_test(tc, s21_from_decimal_to_float_t106);
  tcase_add_test(tc, s21_from_decimal_to_float_t107);
  tcase_add_test(tc, s21_from_decimal_to_float_t201);
  tcase_add_test(tc, s21_from_decimal_to_float_t202);

  suite_add_tcase(s, tc);

  return s;
}

// common part of the tests for s21_from_decimal_to_float func is placed to the
// proc
void test_proc_s21_from_decimal_to_float(const s21_decimal *psrc,
                                         const float *ptdst, const int *ptres) {
#ifdef DEBUG_TEST_S21_FROM_DECIMAL_TO_FLOAT
  printf("DEBUG:  psrc->bits'[3] [2] [1] [0]': '%X %X %X %X'  \n",
         psrc->bits[3], psrc->bits[2], psrc->bits[1], psrc->bits[0]);
  fflush(NULL);
#endif

  float dst = (float)(INT_MAX / 128);

  int res = s21_from_decimal_to_float(*psrc, &dst);
  ck_assert_int_eq((int)res, (int)(*ptres));
  if (res == 0) {
    ck_assert_float_eq((float)dst, (float)(*ptdst));
  } else {
    ck_assert_float_eq((float)dst, (float)(INT_MAX / 128));
  }

#ifdef DEBUG_TEST_S21_FROM_DECIMAL_TO_FLOAT
  fflush(NULL);
#endif
}