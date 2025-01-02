

#include "../helpers/helpers.h"
#include "./s21_decimal_tests.h"

// Положительные целые
START_TEST(add_pos_pos_1) {
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2, 0, 0, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
  // Также должна быть проверка на возвращаемый код
}
END_TEST

START_TEST(add_pos_pos_2) {
  s21_decimal d1 = {{24, 7, 4, 0}};
  s21_decimal d2 = {{40, 6, 6, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{64, 13, 10, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_3) {
  s21_decimal d1 = {{100, 100, 100, 0}};
  s21_decimal d2 = {{100, 100, 100, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{200, 200, 200, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_4) {
  s21_decimal d1 = {{123, 0, 123, 0}};
  s21_decimal d2 = {{123, 0, 123, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{246, 0, 246, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_5) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_6) {
  s21_decimal d1 = {{1000, 1000, 1000, 0}};
  s21_decimal d2 = {{1000, 1000, 1000, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2000, 2000, 2000, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_7) {
  s21_decimal d1 = {{0, 0, 1, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 1, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_8) {
  s21_decimal d1 = {{0, 0, 12, 0}};
  s21_decimal d2 = {{0, 0, 12, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 24, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_9) {
  s21_decimal d1 = {{1000000, 1000000, 1000000, 0}};
  s21_decimal d2 = {{1000000, 1000000, 1000000, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2000000, 2000000, 2000000, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_pos_10) {
  s21_decimal d1 = {{123321, 100, 123321, 0}};
  s21_decimal d2 = {{123321, 100, 123321, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{123321 * 2, 200, 123321 * 2, 0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

// Отрцицательные целые
START_TEST(add_neg_neg_1) {
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2, 0, 0, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_2) {
  s21_decimal d1 = {{24, 7, 4, 0}};
  s21_decimal d2 = {{40, 6, 6, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{64, 13, 10, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_3) {
  s21_decimal d1 = {{100, 100, 100, 0}};
  s21_decimal d2 = {{100, 100, 100, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{200, 200, 200, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_4) {
  s21_decimal d1 = {{123, 0, 123, 0}};
  s21_decimal d2 = {{123, 0, 123, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{246, 0, 246, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_5) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_6) {
  s21_decimal d1 = {{1000, 1000, 1000, 0}};
  s21_decimal d2 = {{1000, 1000, 1000, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2000, 2000, 2000, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_7) {
  s21_decimal d1 = {{0, 0, 1, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 1, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_8) {
  s21_decimal d1 = {{0, 0, 12, 0}};
  s21_decimal d2 = {{0, 0, 12, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 24, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_neg_9) {
  s21_decimal d1 = {{1000000, 1000000, 1000000, 0}};
  s21_decimal d2 = {{1000000, 1000000, 1000000, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{2000000, 2000000, 2000000, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

// Целые + -
START_TEST(add_neg_neg_10) {
  s21_decimal d1 = {{123321, 100, 123321, 0}};
  s21_decimal d2 = {{123321, 100, 123321, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{123321 * 2, 200, 123321 * 2, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

// Целые + -
START_TEST(add_pos_neg_1) {
  s21_decimal d1 = {{123321, 100, 123321, 0}};
  s21_decimal d2 = {{123321, 100, 123321, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 0);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_2) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 0);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_3) {
  s21_decimal d1 = {{123000, 100, 200, 0}};
  s21_decimal d2 = {{1000, 100, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{122000, 0, 199, 0}};
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 0);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_4) {
  s21_decimal d1 = {{100000, 100, 3, 0}};
  s21_decimal d2 = {{100000, 100, 2, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 1, 0}};
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 0);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_5) {
  s21_decimal d1 = {{1, 100, 10000, 0}};
  s21_decimal d2 = {{1, 99, 1000, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 1, 9000, 0}};
  s21_set_sign(&d2, 1);
  s21_set_sign(&expected, 0);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

// Дроби + +
START_TEST(add_decimals_different_scales1) {
  s21_decimal d1 = {{100, 0, 0, 0}};
  s21_decimal d2 = {{100, 0, 0, 0}};

  s21_set_scale(&d1, 1);
  s21_set_scale(&d2, 3);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{10100, 0, 0, 0}};
  s21_set_scale(&expected, 3);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales2) {
  s21_decimal d1 = {{100000, 0, 0, 0}};
  s21_decimal d2 = {{100000, 0, 0, 0}};

  s21_set_scale(&d1, 14);
  s21_set_scale(&d2, 10);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{1000100000, 0, 0, 0}};
  s21_set_scale(&expected, 14);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales3) {
  s21_decimal d1 = {{123456789, 0, 0, 0}};
  s21_decimal d2 = {{98765432, 0, 0, 0}};

  s21_set_scale(&d1, 9);
  s21_set_scale(&d2, 9);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{222222221, 0, 0, 0}};
  s21_set_scale(&expected, 9);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales4) {
  s21_decimal d1 = {{1000000, 0, 0, 0}};
  s21_decimal d2 = {{250000, 0, 0, 0}};

  s21_set_scale(&d1, 4);
  s21_set_scale(&d2, 6);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{100250000, 0, 0, 0}};
  s21_set_scale(&expected, 6);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales5) {
  s21_decimal d1 = {{1000000, 0, 0, 0}};
  s21_decimal d2 = {{250000, 0, 0, 0}};

  s21_set_scale(&d1, 4);
  s21_set_scale(&d2, 6);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{100250000, 0, 0, 0}};
  s21_set_scale(&expected, 6);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

// Дроби - -
START_TEST(add_decimals_different_scales6) {
  s21_decimal d1 = {{1000000, 0, 0, 0}};
  s21_decimal d2 = {{250000, 0, 0, 0}};

  s21_set_scale(&d1, 4);
  s21_set_scale(&d2, 6);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{100250000, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales7) {
  s21_decimal d1 = {{5000, 0, 0, 0}};  // -5.000
  s21_decimal d2 = {{1000, 0, 0, 0}};  // -0.01000

  s21_set_scale(&d1, 3);
  s21_set_scale(&d2, 5);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{501000, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales8) {
  s21_decimal d1 = {{3030, 0, 0, 0}};   // -30.30
  s21_decimal d2 = {{50000, 0, 0, 0}};  // -0.050000

  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 6);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{30350000, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales9) {
  s21_decimal d1 = {{450000, 0, 0, 0}};    // -0.45000
  s21_decimal d2 = {{12345678, 0, 0, 0}};  // -0.12345678

  s21_set_scale(&d1, 6);
  s21_set_scale(&d2, 8);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{57345678, 0, 0, 0}};
  s21_set_scale(&expected, 8);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales10) {
  s21_decimal d1 = {{950, 0, 0, 0}};   // -95.0
  s21_decimal d2 = {{1234, 0, 0, 0}};  // -0.1234

  s21_set_scale(&d1, 1);
  s21_set_scale(&d2, 4);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};

  s21_decimal expected = {{951234, 0, 0, 0}};
  s21_set_scale(&expected, 4);
  s21_set_sign(&expected, 1);

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_decimals_different_scales11) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
  s21_decimal d2 = {{0x1, 0x0, 0x0, 0x0}};

  // Set scales and signs
  s21_set_scale(&d1, 0);
  s21_set_scale(&d2, 0);
  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 0);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0x0, 0x0, 0x1, 0x0}};

  s21_add(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_6) {
  s21_decimal d1 = {{5000, 0, 0, 0}};  // 50.00
  s21_decimal d2 = {{5000, 0, 0, 0}};  // -50.00

  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  int ret = s21_add(d1, d2, &res);

  ck_assert_int_eq(ret, 0);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_7) {
  s21_decimal d1 = {{15000, 0, 0, 0}};  // 150.00
  s21_decimal d2 = {{5000, 0, 0, 0}};   // -50.00

  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 1);  // Negative

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{10000, 0, 0, 0}};  // 100.00

  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 0);

  int ret = s21_add(d1, d2, &res);

  ck_assert_int_eq(ret, 0);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_8) {
  s21_decimal d1 = {{5000, 0, 0, 0}};   // 50.00
  s21_decimal d2 = {{15000, 0, 0, 0}};  // -150.00

  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{10000, 0, 0, 0}};

  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 1);

  int ret = s21_add(d1, d2, &res);

  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_9) {
  // Initialize decimals
  s21_decimal d1 = {{123456789, 0, 0, 0}};  // 1234.56789
  s21_decimal d2 = {{10000, 0, 0, 0}};      // -100.00

  // Set scales
  s21_set_scale(&d1, 5);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 1);  // Negative

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result calculation:
  // 1234.56789 + (-100.00) = 1134.56789

  s21_decimal expected = {{113456789, 0, 0, 0}};  // 1134.56789
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 0);  // Positive

  // Perform addition
  int ret = s21_add(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_pos_neg_10) {
  // Initialize decimals
  s21_decimal d1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Maximum positive value
  s21_decimal d2 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // -Maximum positive value

  // Set scales
  s21_set_scale(&d1, 0);
  s21_set_scale(&d2, 0);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 1);  // Negative

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // Expected result is 0

  // Perform addition
  int ret = s21_add(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_pos_1) {
  // Initialize decimals
  s21_decimal d1 = {{5000, 0, 0, 0}};  // -50.00
  s21_decimal d2 = {{5000, 0, 0, 0}};  // 50.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // Expected result is 0

  // Perform addition
  int ret = s21_add(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_pos_2) {
  // Initialize decimals
  s21_decimal d1 = {{15000, 0, 0, 0}};  // -150.00
  s21_decimal d2 = {{5000, 0, 0, 0}};   // 50.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{10000, 0, 0, 0}};  // -100.00

  // Set expected scale and sign
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 1);  // Negative

  // Perform addition
  int ret = s21_add(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_pos_3) {
  // Initialize decimals
  s21_decimal d1 = {{5000, 0, 0, 0}};   // -50.00
  s21_decimal d2 = {{15000, 0, 0, 0}};  // 150.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{10000, 0, 0, 0}};  // 100.00

  // Set expected scale and sign
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 0);  // Positive

  // Perform addition
  int ret = s21_add(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_pos_4) {
  // Initialize decimals
  s21_decimal d1 = {{123456789, 0, 0, 0}};  // -1234.56789
  s21_decimal d2 = {{10000, 0, 0, 0}};      // 100.00

  // Set scales
  s21_set_scale(&d1, 5);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  s21_decimal res = {{0, 0, 0, 0}};

  // -1234.56789 + 100.00 = -1134.56789

  s21_decimal expected = {{113456789, 0, 0, 0}};  // -1134.56789
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 1);  // Negative

  // Perform addition
  int ret = s21_add(d1, d2, &res);

  ck_assert_int_eq(ret, 0);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(add_neg_pos_5) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  // Set scales
  s21_set_scale(&d1, 0);
  s21_set_scale(&d2, 0);

  // Set signs
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  int ret = s21_add(d1, d2, &res);

  ck_assert_int_eq(ret, 0);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

//==============================================

START_TEST(s21_add_t201) {  // result too big (> +(2^96-1))
  s21_decimal v1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal v2 = {{1, 0, 0, 0x0000000}};
  int tres = 1;  // result too big

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_add(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_add_t202) {  // result too small (< -(2^96-1))
  s21_decimal v1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal v2 = {{1, 0, 0, 0x80000000}};
  int tres = 2;  // result too small

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_add(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);
}
END_TEST

START_TEST(s21_add_t203) {  // bank round check 79..2 + 0.5 = 79..3
  s21_decimal v1 = {{0xFFFFFFFF - 3, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal v2 = {{5, 0, 0, 0x00010000}};  // 0.5
  s21_decimal tdst = {{0xFFFFFFFF - 3 + 1, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  int tres = 0;  //
  // 79228162514264337593543950335 (2^96-1)

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_add(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);

  ck_assert_int_eq((int)dst.bits[0], (int)tdst.bits[0]);
  ck_assert_int_eq((int)dst.bits[1], (int)tdst.bits[1]);
  ck_assert_int_eq((int)dst.bits[2], (int)tdst.bits[2]);
  ck_assert_int_eq((int)dst.bits[3], (int)tdst.bits[3]);
}
END_TEST

START_TEST(s21_add_t204) {  // // bank round check 79..3 + 0.5 = 79..3
  s21_decimal v1 = {{0xFFFFFFFF - 2, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal v2 = {{5, 0, 0, 0x00010000}};  // 0.5
  s21_decimal tdst = {{0xFFFFFFFF - 2, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  int tres = 0;  //
  // 79228162514264337593543950335 (2^96-1)

  s21_decimal dst = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int res = s21_add(v1, v2, &dst);
  ck_assert_int_eq((int)res, (int)tres);

  ck_assert_int_eq((int)dst.bits[0], (int)tdst.bits[0]);
  ck_assert_int_eq((int)dst.bits[1], (int)tdst.bits[1]);
  ck_assert_int_eq((int)dst.bits[2], (int)tdst.bits[2]);
  ck_assert_int_eq((int)dst.bits[3], (int)tdst.bits[3]);
}
END_TEST

//=============================================

Suite *get_suite_s21_add(void) {
  Suite *s = suite_create("\033[44m-=s21_add=-\033[0m");
  TCase *tc = tcase_create("s21_add_tc");

  tcase_add_test(tc, add_pos_pos_1);
  tcase_add_test(tc, add_pos_pos_2);
  tcase_add_test(tc, add_pos_pos_3);
  tcase_add_test(tc, add_pos_pos_4);
  tcase_add_test(tc, add_pos_pos_5);
  tcase_add_test(tc, add_pos_pos_6);
  tcase_add_test(tc, add_pos_pos_7);
  tcase_add_test(tc, add_pos_pos_8);
  tcase_add_test(tc, add_pos_pos_9);
  tcase_add_test(tc, add_pos_pos_10);

  tcase_add_test(tc, add_neg_neg_1);
  tcase_add_test(tc, add_neg_neg_2);
  tcase_add_test(tc, add_neg_neg_3);
  tcase_add_test(tc, add_neg_neg_4);
  tcase_add_test(tc, add_neg_neg_5);
  tcase_add_test(tc, add_neg_neg_6);
  tcase_add_test(tc, add_neg_neg_7);
  tcase_add_test(tc, add_neg_neg_8);
  tcase_add_test(tc, add_neg_neg_9);
  tcase_add_test(tc, add_neg_neg_10);

  tcase_add_test(tc, add_pos_neg_1);
  tcase_add_test(tc, add_pos_neg_2);
  tcase_add_test(tc, add_pos_neg_3);
  tcase_add_test(tc, add_pos_neg_4);
  tcase_add_test(tc, add_pos_neg_5);
  tcase_add_test(tc, add_pos_neg_6);
  tcase_add_test(tc, add_pos_neg_7);
  tcase_add_test(tc, add_pos_neg_8);
  tcase_add_test(tc, add_pos_neg_9);
  tcase_add_test(tc, add_pos_neg_10);

  tcase_add_test(tc, add_neg_pos_1);
  tcase_add_test(tc, add_neg_pos_2);
  tcase_add_test(tc, add_neg_pos_3);
  tcase_add_test(tc, add_neg_pos_4);
  tcase_add_test(tc, add_neg_pos_5);

  tcase_add_test(tc, add_decimals_different_scales1);
  tcase_add_test(tc, add_decimals_different_scales2);
  tcase_add_test(tc, add_decimals_different_scales3);
  tcase_add_test(tc, add_decimals_different_scales4);
  tcase_add_test(tc, add_decimals_different_scales5);
  tcase_add_test(tc, add_decimals_different_scales6);
  tcase_add_test(tc, add_decimals_different_scales7);
  tcase_add_test(tc, add_decimals_different_scales8);
  tcase_add_test(tc, add_decimals_different_scales9);
  tcase_add_test(tc, add_decimals_different_scales10);
  tcase_add_test(tc, add_decimals_different_scales11);

  tcase_add_test(tc, s21_add_t201);
  tcase_add_test(tc, s21_add_t202);
  tcase_add_test(tc, s21_add_t203);
  tcase_add_test(tc, s21_add_t204);

  suite_add_tcase(s, tc);
  return s;
}
