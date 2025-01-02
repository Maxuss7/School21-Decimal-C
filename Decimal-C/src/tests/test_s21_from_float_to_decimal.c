#include "s21_decimal_tests.h"

// #define DEBUG_TEST_S21_FROM_FLOAT_TO_DECIMAL

void test_proc_s21_from_float_to_decimal(const float *psrc,
                                         const s21_decimal *ptdst,
                                         const int *ptres);

#ifdef DEBUG_TEST_S21_FROM_FLOAT_TO_DECIMAL
void test_proc_debug_print_float(float src);
#endif

// 1. ===== Tests with correct parameters (return res = 0) ======
//    1e-28 <= src <= pow(2,96)-1

START_TEST(s21_from_float_to_decimal_t101) {  // src = 0
  float src = 0;
  s21_decimal tdst = {{0, 0, 0, 0x00000000}};
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t102) {  // src = MIN(|s21_decimal|)
  float src = pow(10, -28);
  s21_decimal tdst = {{1, 0, 0, 0x001C0000}};
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t103) {  // src = MAX(|s21_decimal|)
  float src = pow(2, 96) - 1;
  s21_decimal tdst = {{0x20000000, 0xB392B21A, 0xFFFFFF77, 0x00000000}};
  // 79 228 160 000 000 000 000 000 000 000
  // 79228160000000000000000000000 = FFFFFF77 B392B21A 20000000
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t104) {  // src = 1e-22 (keep 7 digits)
  float src = pow(10, -22);
  s21_decimal tdst = {{1000000, 0, 0, 0x001C0000}};
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t105) {  // src = 12345.67890
  float src = 12345.67890;                    // 1.234568e+04
  s21_decimal tdst = {{0x0012D688, 0, 0, 0x00020000}};
  // 1234568 (0x0012D688)
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t106) {  // src = -11111.22222 (minus)
  float src = -11111.22222;                   // // -1.111122e+04
  s21_decimal tdst = {{0x0010F452, 0, 0, 0x80020000}};
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t107) {  // src = 1234567.5 (rounding)
  float src = 1234567.5;                      // -1.234568e+06
  s21_decimal tdst = {{0x0012D688, 0, 0, 0x00000000}};
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t108) {  // src = -1234567.5 (rounding)
  float src = -1234567.5;                     // -1.234568e+06
  s21_decimal tdst = {{0x0012D688, 0, 0, 0x80000000}};
  int tres = 0;
  test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
}
END_TEST

// START_TEST(s21_from_float_to_decimal_t109) {  // src = 12345678*pow(10,-15)
//   float src = pow(10, -15) * 12345678;
//   s21_decimal tdst = {{0x0012D688, 0, 0, 0x000E0000}};
//   int tres = 0;
//   test_proc_s21_from_float_to_decimal(&src, &tdst, &tres);
// }
// END_TEST

// 2. ===== Tests with incorrect parameters  (return res != 0) =====
//   NULL param; src = INFINITY, NAN; src < 1e-28; src > pow(2,96)-1;

START_TEST(s21_from_float_to_decimal_t201) {  // dst = NULL
  float src = 12345.67890;
  // s21_decimal tdst = {{0x0012D688, 0, 0, 0x00020000}};
  int tres = 1;

  // s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_from_float_to_decimal(src, NULL);

  ck_assert_int_eq((int)res, (int)(tres));
}
END_TEST

START_TEST(s21_from_float_to_decimal_t202) {  // src = INFINITY
  float src = INFINITY;
  // s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 1;

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq((int)res, (int)(tres));
  ck_assert_int_eq((int)dst.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[2], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[3], (int)0xFFFFFFFF);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t203) {  // src = NAN
  float src = NAN;
  // s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 1;

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq((int)res, (int)(tres));
  ck_assert_int_eq((int)dst.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[2], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[3], (int)0xFFFFFFFF);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t204) {  // src < 1e-28
  float src = 9.999999e-29;
  s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 1;

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq((int)res, (int)(tres));
  ck_assert_int_eq((int)dst.bits[0], (int)tdst.bits[0]);
  ck_assert_int_eq((int)dst.bits[1], (int)tdst.bits[1]);
  ck_assert_int_eq((int)dst.bits[2], (int)tdst.bits[2]);
  ck_assert_int_eq((int)dst.bits[3], (int)tdst.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_t205) {  // src > pow(2,96)-1;
  float src = pow(2, 97);
  // s21_decimal tdst = {{0, 0, 0, 0}};
  int tres = 1;

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq((int)res, (int)(tres));
  ck_assert_int_eq((int)dst.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[2], (int)0xFFFFFFFF);
  ck_assert_int_eq((int)dst.bits[3], (int)0xFFFFFFFF);
}
END_TEST

// ==============================================================
// Suite setup
// ==============================================================
Suite *get_suite_s21_from_float_to_decimal(void) {
  Suite *s = suite_create("s21_from_float_to_decimal_suite");

  TCase *tc = tcase_create("tc");
  tcase_add_test(tc, s21_from_float_to_decimal_t101);
  tcase_add_test(tc, s21_from_float_to_decimal_t102);
  tcase_add_test(tc, s21_from_float_to_decimal_t103);
  tcase_add_test(tc, s21_from_float_to_decimal_t104);
  tcase_add_test(tc, s21_from_float_to_decimal_t105);
  tcase_add_test(tc, s21_from_float_to_decimal_t106);
  tcase_add_test(tc, s21_from_float_to_decimal_t107);
  tcase_add_test(tc, s21_from_float_to_decimal_t108);
  // tcase_add_test(tc, s21_from_float_to_decimal_t109);
  tcase_add_test(tc, s21_from_float_to_decimal_t201);
  tcase_add_test(tc, s21_from_float_to_decimal_t202);
  tcase_add_test(tc, s21_from_float_to_decimal_t203);
  tcase_add_test(tc, s21_from_float_to_decimal_t204);
  tcase_add_test(tc, s21_from_float_to_decimal_t205);
  suite_add_tcase(s, tc);

  return s;
}

// common part of the tests for s21_from_float_to_decimal func is placed to the
// proc
void test_proc_s21_from_float_to_decimal(const float *psrc,
                                         const s21_decimal *ptdst,
                                         const int *ptres) {
#ifdef DEBUG_TEST_S21_FROM_FLOAT_TO_DECIMAL
  test_proc_debug_print_float(*psrc);
  fflush(NULL);
#endif

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_from_float_to_decimal(*psrc, &dst);

  ck_assert_int_eq((int)res, (int)(*ptres));
  if (res == 0) {
#ifdef DEBUG_TEST_S21_FROM_FLOAT_TO_DECIMAL
    printf("float_src     = %.6e\n", *psrc);
    float tdst_to_float = 0;
    s21_from_decimal_to_float(*ptdst, &tdst_to_float);
    printf("tdst_to_float = %.6e\n", tdst_to_float);
    float dst_to_float = 0;
    s21_from_decimal_to_float(dst, &dst_to_float);
    printf("dst_to_float  = %.6e\n", dst_to_float);
    fflush(NULL);

    printf("DEBUG:  ptsrc->bits'[3] [2] [1] [0]': '%X %X %X %X'  \n",
           ptdst->bits[3], ptdst->bits[2], ptdst->bits[1], ptdst->bits[0]);
    printf("DEBUG:     dst.bits'[3] [2] [1] [0]': '%X %X %X %X'  \n\n",
           dst.bits[3], dst.bits[2], dst.bits[1], dst.bits[0]);
    fflush(NULL);
#endif

    ck_assert_int_eq((int)dst.bits[0], (int)ptdst->bits[0]);
    ck_assert_int_eq((int)dst.bits[1], (int)ptdst->bits[1]);
    ck_assert_int_eq((int)dst.bits[2], (int)ptdst->bits[2]);
    ck_assert_int_eq((int)dst.bits[3], (int)ptdst->bits[3]);
    // ck_assert_mem_eq(&dst, ptdst, sizeof(s21_decimal));
  }
  // else {
  //   ck_assert_int_eq((int)dst.bits[0], (int)0xFFFFFFFF);
  //   ck_assert_int_eq((int)dst.bits[1], (int)0xFFFFFFFF);
  //   ck_assert_int_eq((int)dst.bits[2], (int)0xFFFFFFFF);
  //   ck_assert_int_eq((int)dst.bits[3], (int)0xFFFFFFFF);
  // }
}

#ifdef DEBUG_TEST_S21_FROM_FLOAT_TO_DECIMAL
void test_proc_debug_print_float(float src) {
  unsigned int usrc = *((unsigned int *)(&src));

  printf("DEBUG: float src = %.6e, usrc = %X \n", src, usrc);

  // print_binary((int)usrc);
  unsigned int n = usrc;
  int bits = 32;
  for (int i = bits - 1; i >= 0; i--) {
    int bit = (n >> i) & 1;
    if (i == 30 || i == 22) printf(" ");
    printf("%d", bit);
  }

  // print exp
  int exp = ((usrc & ~(0x80000000)) >> 23) - 127;
  printf("\nexp = %d\n", exp);
  // printf("%.6e\n", src);

  // printf("\n");
  //  fflush(NULL);
}
#endif