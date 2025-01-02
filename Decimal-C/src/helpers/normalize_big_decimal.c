#include "helpers.h"

int s21_normalize_big_decimal(s21_big_decimal *value1,
                              s21_big_decimal *value2) {
  unsigned scale1 = value1->scale;
  unsigned scale2 = value2->scale;

  while (scale1 < scale2) {
    s21_big_decimal_multiply_by_10(value1);
    scale1++;
    value1->scale = scale1;
  }
  while (scale2 < scale1) {
    s21_big_decimal_multiply_by_10(value2);
    scale2++;
    value2->scale = scale2;
  }

  return scale1;
}
