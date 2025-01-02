#include "helpers.h"

void s21_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result) {
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];

  result->bits[3] = 0;
  s21_set_scale(result, value.scale);
  s21_set_sign(result, value.sign);
}
