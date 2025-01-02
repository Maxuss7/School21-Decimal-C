#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_is_zero_decimal(&value_1);
  s21_is_zero_decimal(&value_2);

  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  s21_big_decimal bv_1 = {0, 0, {0}};
  s21_big_decimal bv_2 = {0, 0, {0}};
  s21_decimal_to_big_decimal(value_1, &bv_1);
  s21_decimal_to_big_decimal(value_2, &bv_2);

  s21_normalize_big_decimal(&bv_1, &bv_2);
  // Если знаки разные (0 и 1 или 1 и 0), возвращаем второй знак,
  // так как это определяет результат:
  // - Если sign_2 = 1 (value_2 отрицательное), то value_1 больше.
  // - Если sign_2 = 0 (value_2 положительное), то value_1 меньше.
  if (sign_1 != sign_2) {
    return sign_2;
  }

  // for (int i = 95; i >= 0; i--) {
  for (int i = 255; i >= 0; i--) {
    int bit_1 = s21_big_decimal_get_bit(bv_1, i);
    int bit_2 = s21_big_decimal_get_bit(bv_2, i);
    // Если bit_1 больше, возвращаем противоположный знак первого числа
    if (bit_1 > bit_2) {
      return !sign_1;
    }
    // Если bit_2 > bit_1, то возвращаем знак первого числа.
    if (bit_2 > bit_1) {
      return sign_1;
    }
  }

  // Если все биты равны, то вернуть 0
  return 0;
}