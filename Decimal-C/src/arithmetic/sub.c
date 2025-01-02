#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  s21_big_decimal big_value_1, big_value_2, big_result;
  s21_big_decimal_null(&big_value_1);
  s21_big_decimal_null(&big_value_2);
  s21_big_decimal_null(&big_result);

  s21_decimal_to_big_decimal(value_1, &big_value_1);
  s21_decimal_to_big_decimal(value_2, &big_value_2);

  // Normalize scales
  s21_normalize_big_decimal(&big_value_1, &big_value_2);
  big_result.scale = big_value_1.scale;  // Scales are normalized

  int code = 0;

  if (sign1 == sign2) {
    // Both numbers have the same sign
    s21_sub_same_signs(big_value_1, big_value_2, &big_result);
    // The sign is set inside s21_sub_same_signs
  } else if (sign1 == 0 && sign2 == 1) {
    // Positive minus negative: result = value_1 + |value_2|
    big_value_2.sign = 0;
    s21_add_same_signs(big_value_1, big_value_2, &big_result);
    big_result.sign = 0;  // Result is positive
  } else if (sign1 == 1 && sign2 == 0) {
    // Negative minus positive: result = - (|value_1| + value_2)
    big_value_1.sign = 0;
    s21_add_same_signs(big_value_1, big_value_2, &big_result);
    big_result.sign = 1;  // Result is negative
  }

  if (code == 0) {
    // s21_big_decimal_to_decimal(big_result, result);
    code = s21_big_to_decimal_with_bank_round(big_result, result);
  }

  return code;
}
