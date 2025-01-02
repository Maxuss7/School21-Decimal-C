

#include "../helpers/helpers.h"
#include "./s21_decimal_tests.h"

START_TEST(is_less_1_pos_pos) {
  s21_decimal d1 = {{0xFFFFFFFF, 0x12345678, 0, 0}};
  s21_decimal d2 = {{0xFFFFFFF1, 0x12345678, 0, 0}};

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_2_pos_pos) {
  s21_decimal d1 = {{1, 2, 3, 0}};
  s21_decimal d2 = {{1, 3, 2, 0}};

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_3_pos_pos) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_set_scale(&d2, 5);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_4_pos_pos) {
  s21_decimal d1 = {{0x12345678, 0xFFFFFFFF, 0x12345678, 0}};
  s21_decimal d2 = {{0x12345678, 0xFFFFFFFF, 0x12345678, 0}};
  s21_set_scale(&d1, 7);
  for (int i = 0; i < 7; i++) s21_decimal_multiply_by_10(&d1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_5_pos_pos) {
  s21_decimal d1 = {{0x66666666, 0x66666666, 0, 0}};
  s21_decimal d2 = {{0x66666666, 0x66666666, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 0);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_1_neg_neg) {
  s21_decimal d1 = {{0x66666666, 0x66666666, 0, 0}};
  s21_decimal d2 = {{0x66666666, 0x66666666, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 0);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_2_neg_neg) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFF1, 0, 0}};
  s21_decimal d2 = {{0x66666666, 0xFFFFFFF1, 0, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_3_neg_neg) {
  s21_decimal d1 = {{1, 2, 3, 0}};
  s21_decimal d2 = {{1, 7, 5, 0}};
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_4_neg_neg) {
  s21_decimal d1 = {{123, 321, 0, 0}};
  s21_decimal d2 = {{123, 321, 0, 0}};
  s21_set_scale(&d2, 10);
  s21_set_scale(&d1, 5);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  for (int i = 0; i < 10 - 5; i++) s21_decimal_multiply_by_10(&d2);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_5_neg_neg) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 0);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_1_pos_neg) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 0);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_2_pos_neg) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_3_pos_neg) {
  s21_decimal d1 = {{1, 1000, 90000, 0}};
  s21_decimal d2 = {{1, 1000, 89999, 0}};
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_4_pos_neg) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 0);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_5_pos_neg) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{1, 1, 1, 0}};
  s21_set_sign(&d2, 1);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_1_neg_pos) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 3);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_2_neg_pos) {
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&d1, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_3_neg_pos) {
  s21_decimal d1 = {{1, 1000, 90000, 0}};
  s21_decimal d2 = {{1, 1000, 89999, 0}};
  s21_set_sign(&d1, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_4_neg_pos) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_set_scale(&d2, 20);
  s21_set_scale(&d1, 0);
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 0);

  int res_1 = s21_is_less(d2, d1);
  int res_2 = 0;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(is_less_5_neg_pos) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{1, 1, 1, 0}};
  s21_set_sign(&d1, 1);

  int res_1 = s21_is_less(d1, d2);
  int res_2 = 1;

  ck_assert_int_eq(res_1, res_2);
}
END_TEST

Suite *get_suite_s21_is_less(void) {
  Suite *s = suite_create("\033[44m-=s21_is_less=-\033[0m");
  TCase *tc = tcase_create("s21_is_ls_decimal_tc");

  tcase_add_test(tc, is_less_1_pos_pos);
  tcase_add_test(tc, is_less_2_pos_pos);
  tcase_add_test(tc, is_less_3_pos_pos);
  tcase_add_test(tc, is_less_4_pos_pos);
  tcase_add_test(tc, is_less_5_pos_pos);

  tcase_add_test(tc, is_less_1_neg_neg);
  tcase_add_test(tc, is_less_2_neg_neg);
  tcase_add_test(tc, is_less_3_neg_neg);
  tcase_add_test(tc, is_less_4_neg_neg);
  tcase_add_test(tc, is_less_5_neg_neg);

  tcase_add_test(tc, is_less_1_pos_neg);
  tcase_add_test(tc, is_less_2_pos_neg);
  tcase_add_test(tc, is_less_3_pos_neg);
  tcase_add_test(tc, is_less_4_pos_neg);
  tcase_add_test(tc, is_less_5_pos_neg);

  tcase_add_test(tc, is_less_1_neg_pos);
  tcase_add_test(tc, is_less_2_neg_pos);
  tcase_add_test(tc, is_less_3_neg_pos);
  tcase_add_test(tc, is_less_4_neg_pos);
  tcase_add_test(tc, is_less_5_neg_pos);

  suite_add_tcase(s, tc);
  return s;
}
