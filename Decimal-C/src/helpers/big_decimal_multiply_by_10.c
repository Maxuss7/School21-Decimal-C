#include "helpers.h"

void s21_big_decimal_multiply_by_10(s21_big_decimal *value) {
  s21_big_decimal temp1 = *value;
  s21_big_decimal temp2 = *value;

  s21_shift_left(&temp1, 1);  // temp1 = value * 2
  s21_shift_left(&temp2, 3);  // temp2 = value * 8

  s21_add_same_signs(temp1, temp2, value);
}
