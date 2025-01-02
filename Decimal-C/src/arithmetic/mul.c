#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;

  s21_big_decimal big_value_1, big_value_2, big_result;
  s21_big_decimal_null(&big_value_1);
  s21_big_decimal_null(&big_value_2);
  s21_big_decimal_null(&big_result);

  s21_decimal_to_big_decimal(value_1, &big_value_1);
  s21_decimal_to_big_decimal(value_2, &big_value_2);

  s21_big_decimal_mul(big_value_1, big_value_2, &big_result);

  // s21_big_decimal_to_decimal(big_result, result);
  err = s21_big_to_decimal_with_bank_round(big_result, result);

  return err;
}