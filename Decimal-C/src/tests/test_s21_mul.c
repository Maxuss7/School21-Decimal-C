

#include "../helpers/helpers.h"
#include "./s21_decimal_tests.h"

// Положительные целые
START_TEST(mul_pos_pos_1) {
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{1, 0, 0, 0}};

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
  // Также должна быть проверка на возвращаемый код
}
END_TEST

START_TEST(mul_pos_pos_2) {
  s21_decimal d1 = {{2, 0, 0, 0}};
  s21_decimal d2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{6, 0, 0, 0}};

  int status = s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(mul_pos_pos_3) {
  s21_decimal d1 = {{123456, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(status, 0);  // Проверка кода успеха
}
END_TEST

START_TEST(mul_pos_pos_4) {
  s21_decimal d1 = {{987654321, 0, 0, 0}};  // Число 987,654,321
  s21_decimal d2 = {{1, 0, 0, 0}};          // Число 1
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {
      {987654321, 0, 0, 0}};  // Ожидаемое значение 987,654,321

  int status = s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(status, 0);  // Проверка кода успеха
}
END_TEST

START_TEST(mul_pos_pos_5) {
  // d1 = 2^31 = 2147483648 (0x80000000)
  s21_decimal d1 = {{0x80000000, 0, 0, 0}};

  // d2 = 2
  s21_decimal d2 = {{2, 0, 0, 0}};

  // Ожидаемый результат после умножения:
  // 2^31 * 2 = 2^32 = 4294967296, что в 32-битном представлении будет
  // {{0, 1, 0, 0}}, так как результат сместится в старший 32-битный блок.
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 1, 0, 0}};

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_pos_pos_6) {
  // d1 = 2^30 = 1073741824 (0x40000000)
  s21_decimal d1 = {{0x40000000, 0, 0, 0}};

  // d2 = 2^30 = 1073741824 (0x40000000)
  s21_decimal d2 = {{0x40000000, 0, 0, 0}};

  // Ожидаемый результат:
  // 2^30 * 2^30 = 2^60 = 1152921504606846976

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0x00000000, 0x10000000, 0x00000000, 0x00000000}};

  s21_mul(d1, d2, &res);
  //   printf("Result: %08X %08X %08X %08X\n", res.bits[3], res.bits[2],
  //   res.bits[1],
  //          res.bits[0]);
  //   printf("Expected: %08X %08X %08X %08X\n", expected.bits[3],
  //   expected.bits[2],
  //          expected.bits[1], expected.bits[0]);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_pos_pos_7) {
  s21_decimal d1 = {{12345, 0, 0, 0}};
  s21_set_scale(&d1, 2);

  s21_decimal d2 = {{67, 0, 0, 0}};
  s21_set_scale(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{827115, 0, 0, 0}};
  s21_set_scale(&expected, 3);

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_pos_pos_8) {
  s21_decimal d1 = {{12345, 0, 0, 0}};
  s21_set_scale(&d1, 10);

  s21_decimal d2 = {{67, 0, 0, 0}};
  s21_set_scale(&d2, 7);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{827115, 0, 0, 0}};
  s21_set_scale(&expected, 17);

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_pos_pos_9) {
  s21_decimal value_1 = {{0x00001000, 0x00000000, 0x00000001, 0x00000000}};
  s21_decimal value_2 = {{0x00002000, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res;
  s21_decimal predict = {{0x02000000, 0x00000000, 0x00002000, 0x80000000}};
  s21_mul(value_1, value_2, &res);
  ck_assert_uint_eq(res.bits[0], predict.bits[0]);
  ck_assert_uint_eq(res.bits[1], predict.bits[1]);
  ck_assert_uint_eq(res.bits[2], predict.bits[2]);
  ck_assert_uint_eq(res.bits[3], predict.bits[3]);
}
END_TEST

START_TEST(mul_neg_neg_1) {
  s21_decimal d1 = {{12345, 0, 0, 0}};
  s21_set_scale(&d1, 10);
  s21_set_sign(&d1, 1);

  s21_decimal d2 = {{67, 0, 0, 0}};
  s21_set_scale(&d2, 7);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{827115, 0, 0, 0}};
  s21_set_scale(&expected, 17);
  s21_set_sign(&expected, 0);

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_neg_neg_2) {
  s21_decimal d1 = {{1000, 0, 0, 0}};
  s21_set_scale(&d1, 2);
  s21_set_sign(&d1, 1);

  s21_decimal d2 = {{2000, 0, 0, 0}};
  s21_set_scale(&d2, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2000000, 0, 0, 0}};
  s21_set_scale(&expected, 3);
  s21_set_sign(&expected, 0);

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_pos_neg_1) {
  s21_decimal d1 = {{12345, 0, 0, 0}};
  s21_set_scale(&d1, 2);
  s21_set_sign(&d1, 0);

  s21_decimal d2 = {{67, 0, 0, 0}};
  s21_set_scale(&d2, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{827115, 0, 0, 0}};
  s21_set_scale(&expected, 3);
  s21_set_sign(&expected, 1);

  s21_mul(d1, d2, &res);

  // Verify the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(mul_neg_pos_1) {
  s21_decimal d1 = {{12345, 0, 0, 0}};
  s21_set_scale(&d1, 2);
  s21_set_sign(&d1, 1);

  s21_decimal d2 = {{67, 0, 0, 0}};
  s21_set_scale(&d2, 1);
  s21_set_sign(&d2, 0);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{827115, 0, 0, 0}};
  s21_set_scale(&expected, 3);
  s21_set_sign(&expected, 1);

  s21_mul(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *get_suite_s21_mul(void) {
  Suite *s = suite_create("\033[44m-=s21_mul=-\033[0m");
  TCase *tc = tcase_create("s21_mul_tc");

  tcase_add_test(tc, mul_pos_pos_1);
  tcase_add_test(tc, mul_pos_pos_2);
  tcase_add_test(tc, mul_pos_pos_3);
  tcase_add_test(tc, mul_pos_pos_4);
  tcase_add_test(tc, mul_pos_pos_5);
  tcase_add_test(tc, mul_pos_pos_6);
  tcase_add_test(tc, mul_pos_pos_7);
  tcase_add_test(tc, mul_pos_pos_8);
  tcase_add_test(tc, mul_pos_pos_9);

  tcase_add_test(tc, mul_neg_neg_1);
  tcase_add_test(tc, mul_neg_neg_2);
  tcase_add_test(tc, mul_pos_neg_1);
  tcase_add_test(tc, mul_neg_pos_1);

  suite_add_tcase(s, tc);
  return s;
}
