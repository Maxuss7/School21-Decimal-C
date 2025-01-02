

#include "../helpers/helpers.h"
#include "./s21_decimal_tests.h"

// Децималы со скейлами 0 0
START_TEST(is_not_equal_1_pos_pos) {
  s21_decimal d1 = {{0xFFFFFFFF, 0x12345678, 0, 0}};
  s21_decimal d2 = {{0xFFFFFFF1, 0x12345678, 0, 0}};

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;

  //   print_decimal(&d1);
  //   printf("\n");
  //   print_decimal(&d2);
  //   printf("----------------------\n");

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

// Децималы с разными скейлами, но одинаковые по значению
START_TEST(is_not_equal_2_pos_pos) {
  s21_decimal d1 = {{0xFF123456, 0xFFFFA912, 0x0000000F, 0}};
  s21_decimal d2 = {{0xFF123456, 0xFFFFA912, 0x0000000F, 0}};

  s21_set_scale(&d1, 0);
  s21_set_scale(&d2, 3);
  s21_decimal_multiply_by_10(&d2);
  s21_decimal_multiply_by_10(&d2);
  s21_decimal_multiply_by_10(&d2);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_3_pos_pos) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  s21_set_scale(&d1, 20);
  s21_set_scale(&d2, 3);
  for (int i = 0; i < 20 - 3; i++) {
    s21_decimal_multiply_by_10(&d1);
  }

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_4_pos_pos) {
  s21_decimal d1 = {{0xFF123456, 0xAAAAAAAA, 0xBBBBBBBB, 0}};
  s21_decimal d2 = {{0xFF123456, 0xAAAAAAAA, 0xBBBBBBBB, 0}};

  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 0);
  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_5_pos_pos) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};

  s21_set_scale(&d1, 0);
  s21_set_scale(&d2, 3);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_1_neg_neg) {
  s21_decimal d1 = {{0xFFFFFF0, 0x98765432, 0x11235DD2, 0}};
  s21_decimal d2 = {{0x98765432, 0x99999999, 0x11235DD2, 0}};
  s21_set_scale(&d1, 10);
  s21_set_scale(&d2, 10);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_2_neg_neg) {
  s21_decimal d1 = {{0x11111111, 0x1111FFFF, 0xFFFF1111, 0}};
  s21_decimal d2 = {{0x11111111, 0x1111FFFF, 0xFFFF1111, 0}};
  s21_set_scale(&d1, 20);
  s21_set_scale(&d2, 20);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_3_neg_neg) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&d1, 10);
  s21_set_scale(&d2, 10);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_4_neg_neg) {
  s21_decimal d1 = {{1, 1, 1, 0}};
  s21_decimal d2 = {{1, 1, 1, 0}};
  s21_set_scale(&d1, 10);
  s21_set_scale(&d2, 7);
  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

// Оставил эту штуку на всякий случай
// здесь у нас переполнение после умножения, ошибку бы выдать
START_TEST(is_not_equal_5_neg_neg) {
  s21_decimal d1 = {{1, 1, 1, 0}};
  s21_decimal d2 = {{1, 1, 1, 0}};
  s21_set_scale(&d1, 10);
  s21_set_scale(&d2, 7);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_1_pos_neg) {
  s21_decimal d1 = {{0x111FF111, 0x1111FFFF, 0xFFFFCCCC, 0}};
  s21_decimal d2 = {{0x111FF111, 0x1111FFFF, 0xFFFFCCCC, 0}};
  s21_set_scale(&d1, 5);
  s21_set_scale(&d2, 8);
  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_2_pos_neg) {
  s21_decimal d1 = {{0x111FF111, 0xFFFFFFFF, 0xFFFFAAAA, 0}};
  s21_decimal d2 = {{0x111FF111, 0xFFFFFFFF, 0xFFFFAAAA, 0}};
  s21_set_scale(&d1, 5);
  s21_set_scale(&d2, 8);
  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_3_pos_neg) {
  s21_decimal d1 = {{0x0F0F0F0F, 0x1111FFFF, 0xAFFFAAAA, 0}};
  s21_decimal d2 = {{0x0F0F0F0F, 0x1111FFFF, 0xAFFFAAAA, 0}};
  s21_set_scale(&d1, 2);
  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);
  s21_set_scale(&d2, 0);
  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d2, d1);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_4_pos_neg) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};

  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d2, d1);
  int res_2 = 0;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_5_pos_neg) {
  s21_decimal d1 = {{0x0F0F0F0F, 0x1111FFFF, 0xAFFFAAAA, 0}};
  s21_decimal d2 = {{0x0F0F0F0F, 0x1111FFFF, 0xAFFFAAAA, 0}};
  s21_set_scale(&d1, 2);
  s21_decimal_multiply_by_10(&d1);
  s21_decimal_multiply_by_10(&d1);
  s21_set_scale(&d2, 0);
  s21_set_sign(&d1, 0);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_not_equal(d2, d1);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_1_neg_pos) {
  s21_decimal d1 = {{0x0F0F0F0F, 0x1234FFFF, 0xAFFFAAAA, 0}};
  s21_decimal d2 = {{0x0F0F0F0F, 0x1234FFFF, 0xAFFFAAAA, 0}};
  s21_set_scale(&d1, 3);
  s21_set_scale(&d2, 28);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);
  for (int i = 0; i < 28 - 3; i++) {
    s21_decimal_multiply_by_10(&d2);
  }

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_2_neg_pos) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};

  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_3_neg_pos) {
  s21_decimal d1 = {{0xFFFFFF, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0xFFFFFF, 0}};

  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_4_neg_pos) {
  s21_decimal d1 = {{0, 0xFFFABC, 0, 0}};
  s21_decimal d2 = {{0, 0xFFFABC, 0, 0}};

  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_not_equal_5_neg_pos) {
  s21_decimal d1 = {{0xABCD1234, 0, 0, 0}};
  s21_decimal d2 = {{0xABCD4321, 0, 0, 0}};

  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_not_equal(d1, d2);
  int res_2 = 1;
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

Suite *get_suite_s21_is_not_equal(void) {
  Suite *s = suite_create("\033[44m-=s21_is_not_equal=-\033[0m");
  TCase *tc = tcase_create("s21_not_eq_decimal_tc");

  tcase_add_test(tc, is_not_equal_1_pos_pos);
  tcase_add_test(tc, is_not_equal_2_pos_pos);
  tcase_add_test(tc, is_not_equal_3_pos_pos);
  tcase_add_test(tc, is_not_equal_4_pos_pos);
  tcase_add_test(tc, is_not_equal_5_pos_pos);

  tcase_add_test(tc, is_not_equal_1_neg_neg);
  tcase_add_test(tc, is_not_equal_2_neg_neg);
  tcase_add_test(tc, is_not_equal_3_neg_neg);
  tcase_add_test(tc, is_not_equal_4_neg_neg);
  tcase_add_test(tc, is_not_equal_5_neg_neg);

  tcase_add_test(tc, is_not_equal_1_pos_neg);
  tcase_add_test(tc, is_not_equal_2_pos_neg);
  tcase_add_test(tc, is_not_equal_3_pos_neg);
  tcase_add_test(tc, is_not_equal_4_pos_neg);
  tcase_add_test(tc, is_not_equal_5_pos_neg);

  tcase_add_test(tc, is_not_equal_1_neg_pos);
  tcase_add_test(tc, is_not_equal_2_neg_pos);
  tcase_add_test(tc, is_not_equal_3_neg_pos);
  tcase_add_test(tc, is_not_equal_4_neg_pos);
  tcase_add_test(tc, is_not_equal_5_neg_pos);

  suite_add_tcase(s, tc);
  return s;
}
