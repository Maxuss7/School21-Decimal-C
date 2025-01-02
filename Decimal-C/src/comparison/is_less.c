#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_is_zero_decimal(&value_1);
  s21_is_zero_decimal(&value_2);

  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  s21_big_decimal bv_1 = {0, 0, {0}};
  s21_big_decimal bv_2 = {0, 0, {0}};
  s21_decimal_to_big_decimal(value_1, &bv_1);
  s21_decimal_to_big_decimal(value_2, &bv_2);

  s21_normalize_big_decimal(&bv_1, &bv_2);

  if (sign_1 != sign_2) {
    return sign_1;
  }

  for (int i = 255; i >= 0; i--) {
    int bit_1 = s21_big_decimal_get_bit(bv_1, i);
    int bit_2 = s21_big_decimal_get_bit(bv_2, i);

    if (bit_1 > bit_2) {
      return sign_1;
    }

    if (bit_2 > bit_1) {
      return !sign_1;
    }
  }

  // Если все биты равны, то вернуть 0
  return 0;
}
