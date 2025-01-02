#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  s21_normalize_decimal(&value1, &value2);
  s21_is_zero_decimal(&value1);
  s21_is_zero_decimal(&value2);

  int v1_sign = s21_get_sign(value1);
  int v2_sign = s21_get_sign(value2);

  int is_equal;
  if (v1_sign != v2_sign)
    is_equal = 0;
  else
    is_equal = s21_is_equal_bits_decimal(value1, value2);

  return is_equal;
}