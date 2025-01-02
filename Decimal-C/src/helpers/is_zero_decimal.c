#include "helpers.h"

int s21_is_zero_decimal(s21_decimal *value) {
  int is_zero = 1;
  for (int i = 0; i < DEC_BITS / 4 * 3; i++) {
    if (s21_get_bit(*value, i) != 0) {
      is_zero = 0;
      break;
    }
  }
  if (is_zero) {
    s21_set_sign(value, 0);
    s21_set_scale(value, 0);
  }
  return is_zero;
}

int s21_is_0_decimal(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

int s21_is_0_big_decimal(s21_big_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
          value.bits[3] == 0 && value.bits[4] == 0 && value.bits[5] == 0 &&
          value.bits[6] == 0 && value.bits[7] == 0);
}