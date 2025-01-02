#include "s21_decimal_tests.h"

// #define DEBUG_TEST_S21_NEGATE

void test_proc_s21_negate(const s21_decimal *psrc, const s21_decimal *ptdst,
                          const int *ptres);

// 1. Tests with correct parameters (return res = 0)

START_TEST(s21_negate_t101) {  // src = +0
  s21_decimal src = {{0, 0, 0, 0x00000000}};
  s21_decimal tdst = {{0, 0, 0, 0x80000000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t102) {  // src = -0
  s21_decimal src = {{0, 0, 0, 0x80000000}};
  s21_decimal tdst = {{0, 0, 0, 0x00000000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t103) {  // src > 0  (scale = 0)
  s21_decimal src = {{0x11111111, 0x22222222, 0x33333333, 0x00000000}};
  s21_decimal tdst = {{0x11111111, 0x22222222, 0x33333333, 0x80000000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t104) {  // src < 0  (scale = 0)
  s21_decimal src = {{0x11111111, 0x22222222, 0x33333333, 0x80000000}};
  s21_decimal tdst = {{0x11111111, 0x22222222, 0x33333333, 0x00000000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t105) {  // src = +0  (scale = 5)
  s21_decimal src = {{0, 0, 0, 0x00050000}};
  s21_decimal tdst = {{0, 0, 0, 0x80050000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t106) {  // src = -0  (scale = 5)
  s21_decimal src = {{0, 0, 0, 0x80050000}};
  s21_decimal tdst = {{0, 0, 0, 0x00050000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t107) {  // src > 0 (scale = 5)
  s21_decimal src = {{1234567890, 0, 0, 0x00050000}};
  s21_decimal tdst = {{1234567890, 0, 0, 0x80050000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t108) {  // src < 0 (scale = 5)
  s21_decimal src = {{1234567890, 0, 0, 0x80050000}};
  s21_decimal tdst = {{1234567890, 0, 0, 0x00050000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t109) {  // src = +MAX_MANTISSA (scale = 1)
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  s21_decimal tdst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 79228162514264337593543950335 / 10^1 = 19999999 99999999 99999999 (+0.5)
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t110) {  // src = -MAX_MANTISSA (scale = 1)
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal tdst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  // 79228162514264337593543950335 / 10^1 = 0x199999999999999999999999 (+0.5)
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t111) {  // src => +MAX_MANTISSA,  scale = 28 (MAX)
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal tdst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950335 / 10^28 = 0x7  (+ ~0.922816)
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t112) {  // src => -MAX_MANTISSA,  scale = 28 (MAX)
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal tdst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  // 79228162514264337593543950335 / 10^28 = 0x7  (+ ~0.922816)
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t113) {  // src = +1e-28
  s21_decimal src = {{0x00000001, 0, 0, 0x001C0000}};
  s21_decimal tdst = {{0x00000001, 0, 0, 0x801C0000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_negate_t114) {  // src = -1e-28
  s21_decimal src = {{0x00000001, 0, 0, 0x801C0000}};
  s21_decimal tdst = {{0x00000001, 0, 0, 0x001C0000}};
  int tres = 0;
  test_proc_s21_negate(&src, &tdst, &tres);
}
END_TEST

// 2. Tests with incorrect parameters (return res != 0)

START_TEST(s21_negate_t201) {  // test s21_decimal dst == NULL
  s21_decimal src = {{1234567890, 0, 0, 0x00050000}};
  // s21_decimal tdst = {{12345, 0, 0, 0x00000000}};
  int tres = 1;

  // s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_negate(src, NULL);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_negate_t202) {  // test s21_decimal src is incorrect
  s21_decimal src = {{1234567890, 0, 0, 0x01050011}};
  // s21_decimal tdst = {{12345, 0, 0, 0x00000000}};
  int tres = 1;

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_negate(src, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_negate_t203) {  // test s21_decimal scale is incorrect (>28)
  s21_decimal src = {{1234567890, 0, 0, 0x001D0000}};
  // s21_decimal tdst = {{12345, 0, 0, 0x00000000}};
  int tres = 1;

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_negate(src, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

// ==============================================================
// Suite setup
// ==============================================================
Suite *get_suite_s21_negate(void) {
  Suite *s = suite_create("s21_negate_suite");

  TCase *tc = tcase_create("tc");
  tcase_add_test(tc, s21_negate_t101);
  tcase_add_test(tc, s21_negate_t102);
  tcase_add_test(tc, s21_negate_t103);
  tcase_add_test(tc, s21_negate_t104);
  tcase_add_test(tc, s21_negate_t105);
  tcase_add_test(tc, s21_negate_t106);
  tcase_add_test(tc, s21_negate_t107);
  tcase_add_test(tc, s21_negate_t108);
  tcase_add_test(tc, s21_negate_t109);
  tcase_add_test(tc, s21_negate_t110);
  tcase_add_test(tc, s21_negate_t111);
  tcase_add_test(tc, s21_negate_t112);
  tcase_add_test(tc, s21_negate_t113);
  tcase_add_test(tc, s21_negate_t114);
  tcase_add_test(tc, s21_negate_t201);
  tcase_add_test(tc, s21_negate_t202);
  tcase_add_test(tc, s21_negate_t203);
  suite_add_tcase(s, tc);

  return s;
}

// common part of the tests for s21_negate func is placed to the
// proc
void test_proc_s21_negate(const s21_decimal *psrc, const s21_decimal *ptdst,
                          const int *ptres) {
#ifdef DEBUG_TEST_S21_NEGATE
  printf("DEBUG:  psrc->bits'[3] [2] [1] [0]': '%X %X %X %X'  \n",
         psrc->bits[3], psrc->bits[2], psrc->bits[1], psrc->bits[0]);
  fflush(NULL);
#endif

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};

  int res = s21_negate(*psrc, &dst);
  ck_assert_int_eq((int)res, (int)(*ptres));

  ck_assert_int_eq((int)dst.bits[0], (int)ptdst->bits[0]);
  ck_assert_int_eq((int)dst.bits[1], (int)ptdst->bits[1]);
  ck_assert_int_eq((int)dst.bits[2], (int)ptdst->bits[2]);
  ck_assert_int_eq((int)dst.bits[3], (int)ptdst->bits[3]);

  // ck_assert_mem_eq(&dst, ptdst, sizeof(s21_decimal));

#ifdef DEBUG_TEST_S21_NEGATE
  fflush(NULL);
#endif
}