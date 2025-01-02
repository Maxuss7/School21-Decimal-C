#include "helpers.h"

void s21_big_decimal_null(s21_big_decimal* value) {
  for (int i = 0; i < 8; i++) {
    value->bits[i] = 0;
  }
  value->scale = 0;
  value->sign = 0;
}
