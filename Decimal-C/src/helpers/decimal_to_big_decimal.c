#include "helpers.h"

void s21_decimal_to_big_decimal(s21_decimal value, s21_big_decimal *result) {
  s21_big_decimal_null(result);

  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];

  result->scale = s21_get_scale(value);
  result->sign = s21_get_sign(value);
  result->scale = s21_get_scale(value);
  result->sign = s21_get_sign(value);
}