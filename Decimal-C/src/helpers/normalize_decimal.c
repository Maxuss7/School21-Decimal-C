#include "helpers.h"

// Обертка чтобы нормализовывать decimal
// через normalize_scales для s21_big_decimal
int s21_normalize_decimal(s21_decimal *value1, s21_decimal *value2) {
  s21_big_decimal bd1;
  s21_big_decimal bd2;

  s21_decimal_to_big_decimal(*value1, &bd1);
  s21_decimal_to_big_decimal(*value2, &bd2);

  s21_normalize_big_decimal(&bd1, &bd2);

  int scale = bd1.scale;

  s21_big_decimal_to_decimal(bd1, value1);
  s21_big_decimal_to_decimal(bd2, value2);

  s21_set_scale(value1, scale);
  s21_set_scale(value2, scale);

  return scale;
}