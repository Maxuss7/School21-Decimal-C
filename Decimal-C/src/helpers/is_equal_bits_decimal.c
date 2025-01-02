#include "helpers.h"

int s21_is_equal_bits_decimal(s21_decimal value1, s21_decimal value2) {
  int is_equal = 1;
  for (int i = 0; i < DEC_BITS; i++) {
    if (s21_get_bit(value1, i) != s21_get_bit(value2, i)) {
      is_equal = 0;
      break;
    }
  }
  return is_equal;
}