#include "s21_decimal_tests.h"

// #define DEBUG_TEST_S21_DIV

void test_proc_s21_div(const s21_decimal *pv1, const s21_decimal *pv2,
                       const s21_decimal *ptdst, const int *ptres);

// 1. Tests with correct parameters (return res = 0)

START_TEST(s21_div_t101) {  // 0 / MAX = 0
  s21_decimal v1 = {{0, 0, 0, 0}};
  s21_decimal v2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t102) {  // 0 / MIN_MOD = 0
  s21_decimal v1 = {{0, 0, 0, 0}};
  s21_decimal v2 = {{1, 0, 0, 0x001C0000}};  // 1e-28
  s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t103) {  // 10 / -5 = -2
  s21_decimal v1 = {{10, 0, 0, 0}};
  s21_decimal v2 = {{5, 0, 0, 0x80000000}};
  s21_decimal tdst = {{2, 0, 0, 0x80000000}};
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t104) {  // +MAX / 100 = 79228162514264337593543950335e-2
  s21_decimal v1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal v2 = {{100, 0, 0, 0}};
  // 79228162514264337593543950335/10^2 = 0x28F5C28 F5C28F5C 28F5C28F
  // (+0.35)
  // 79228162514264337593543950335(9): mantissa for MAX rounding =
  // = 0x9 FFFFFFFF FFFFFFFF FFFFFFFF
  // s21_decimal tdst = {{0x28F5C28F, 0xF5C28F5C, 0x028F5C28, 0x00000000}};
  s21_decimal tdst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00020000}};
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t105) {  // +MAX / -MAX = -1
  s21_decimal v1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal v2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal tdst = {{1, 0, 0, 0x80000000}};
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t106) {  // 1234567890*1e-2 / 1234567890*1e-1 = 1e-1
  s21_decimal v1 = {{1234567890, 0, 0, 0x00020000}};
  s21_decimal v2 = {{1234567890, 0, 0, 0x00010000}};
  s21_decimal tdst = {{10, 0, 0, 0x00020000}};  // 10e-2 == 1e-1
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t107) {  // 1 / 3 = 0.333333)
  s21_decimal v1 = {{1, 0, 0, 0x00000000}};
  s21_decimal v2 = {{3, 0, 0, 0x00000000}};
  s21_decimal tdst = {
      {0x5555555, 0x14B700CB, 0xAC544CA, 0x001C0000}};  // 0.333333)
  // 6BB4AFE4 CF2607EE 35555555 // 33333..33 (29 digits)
  // AC544CA 14B700CB 05555555 // 33333..33 (28 digits)

  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t108) {  // 0.001 / 0.00003 = 33.3333)
  s21_decimal v1 = {{1, 0, 0, 0x0030000}};
  s21_decimal v2 = {{3, 0, 0, 0x0050000}};
  s21_decimal tdst = {{0x35555555, 0xCF2607EE, 0x6BB4AFE4, 0x001B0000}};
  // dst.bits'[3] [2] [1] [0]': '1B0000 6BB4AFE4 CF2607EE 35555555'
  // 6BB4AFE4 CF2607EE 35555555 // 33333..33 (29 digits)
  // AC544CA 14B700CB 05555555 // 33333..33 (28 digits)

  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

START_TEST(s21_div_t109) {  // 1 / 6 = 0.1666...667)
  s21_decimal v1 = {{1, 0, 0, 0x00000000}};
  s21_decimal v2 = {{6, 0, 0, 0x00000000}};
  s21_decimal tdst = {{0x82AAAAAB, 0xA5B8065, 0x562A265, 0x001C0000}};
  // '1C0000 562A265 A5B8065 82AAAAAB' '001C0000 0562A2650A5B806582AAAAAB'
  int tres = 0;
  test_proc_s21_div(&v1, &v2, &tdst, &tres);
}
END_TEST

// not passed - TODO
// START_TEST(s21_div_t110) {  // +MAX*1e10-5 / +MAX*1e10-3 = 1e10-2
//   s21_decimal v1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00050000}};
//   s21_decimal v2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00030000}};
//   s21_decimal tdst = {{1, 0, 0, 0x00020000}};
//   int tres = 0;
//   test_proc_s21_div(&v1, &v2, &tdst, &tres);
// }
// END_TEST

// 2. Tests with incorrect parameters (return res != 0)
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

START_TEST(s21_div_t201) {  // incorrect paramenter result = NULL
  s21_decimal v1 = {{10, 0, 0, 0x80000000}};
  s21_decimal v2 = {{5, 0, 0, 0x80000000}};
  int tres = -1;  // incorrect paramenter

  // s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_div(v1, v2, NULL);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_div_t202) {  // v1 is incorrect
  s21_decimal v1 = {{10, 0, 0, 0x80000011}};
  s21_decimal v2 = {{5, 0, 0, 0x80000000}};
  int tres = -1;  // incorrect paramenter

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_div(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_div_t203) {  // v2 is incorrect (scale>28)
  s21_decimal v1 = {{10, 0, 0, 0x00000000}};
  s21_decimal v2 = {{5, 0, 0, 0x001D0000}};
  int tres = -1;  // incorrect paramenter

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_div(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_div_t204) {  // division_by_zero
  s21_decimal v1 = {{10, 0, 0, 0x00000000}};
  s21_decimal v2 = {{0, 0, 0, 0x00000000}};
  int tres = 3;  // division_by_zero

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_div(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_div_t205) {  // result too big (> +(2^96-1))
  s21_decimal v1 = {{100, 0, 0, 0x00000000}};
  s21_decimal v2 = {{1, 0, 0, 0x001C0000}};
  int tres = 1;  // result too big

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_div(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_div_t206) {  // result too small (< -(2^96-1))
  s21_decimal v1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal v2 = {{1, 0, 0, 0x001C0000}};
  int tres = 2;  // result too small

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_div(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

// ==============================================================
// Suite setup
// ==============================================================
Suite *get_suite_s21_div(void) {
  Suite *s = suite_create("s21_div_suite");

  TCase *tc = tcase_create("tc");
  tcase_add_test(tc, s21_div_t101);
  tcase_add_test(tc, s21_div_t102);
  tcase_add_test(tc, s21_div_t103);
  tcase_add_test(tc, s21_div_t104);
  tcase_add_test(tc, s21_div_t105);
  tcase_add_test(tc, s21_div_t106);
  tcase_add_test(tc, s21_div_t107);
  tcase_add_test(tc, s21_div_t108);
  tcase_add_test(tc, s21_div_t109);
  // tcase_add_test(tc, s21_div_t110); // not passed >> TODO

  tcase_add_test(tc, s21_div_t201);
  tcase_add_test(tc, s21_div_t202);
  tcase_add_test(tc, s21_div_t203);
  tcase_add_test(tc, s21_div_t204);
  tcase_add_test(tc, s21_div_t205);
  tcase_add_test(tc, s21_div_t206);
  suite_add_tcase(s, tc);

  return s;
}

// common part of the tests for s21_div func is placed to the
// proc
void test_proc_s21_div(const s21_decimal *pv1, const s21_decimal *pv2,
                       const s21_decimal *ptdst, const int *ptres) {
#ifdef DEBUG_TEST_S21_DIV
  printf("DEBUG:  ptdst->bits'[3] [2] [1] [0]': '%X %X %X %X'  \n",
         ptdst->bits[3], ptdst->bits[2], ptdst->bits[1], ptdst->bits[0]);
  fflush(NULL);
#endif

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};

  int res = s21_div(*pv1, *pv2, &dst);

#ifdef DEBUG_TEST_S21_DIV
  printf("DEBUG:     dst.bits'[3] [2] [1] [0]': '%X %X %X %X'  \n", dst.bits[3],
         dst.bits[2], dst.bits[1], dst.bits[0]);

  float tdst_to_float = 0;
  s21_from_decimal_to_float(*ptdst, &tdst_to_float);
  printf("tdst_to_float = %.6e\n", tdst_to_float);

  float dst_to_float = 0;
  s21_from_decimal_to_float(dst, &dst_to_float);
  printf(" dst_to_float = %.6e\n", dst_to_float);

  fflush(NULL);
#endif

  ck_assert_int_eq((int)res, (int)(*ptres));

  ck_assert_int_eq(s21_is_equal(dst, *ptdst), 1);

  // ck_assert_int_eq((int)dst.bits[0], (int)ptdst->bits[0]);
  // ck_assert_int_eq((int)dst.bits[1], (int)ptdst->bits[1]);
  // ck_assert_int_eq((int)dst.bits[2], (int)ptdst->bits[2]);
  // ck_assert_int_eq((int)dst.bits[3], (int)ptdst->bits[3]);

  // ck_assert_mem_eq(&dst, ptdst, sizeof(s21_decimal));

#ifdef DEBUG_TEST_S21_DIV
  fflush(NULL);
#endif
}