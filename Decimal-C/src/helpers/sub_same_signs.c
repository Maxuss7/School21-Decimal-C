#include "helpers.h"

int s21_big_decimal_compare_abs(s21_big_decimal value1,
                                s21_big_decimal value2) {
  int cmp = 0;
  for (int i = 7; i >= 0; i--) {
    if (value1.bits[i] > value2.bits[i]) {
      cmp = 1;
      break;
    } else if (value1.bits[i] < value2.bits[i]) {
      cmp = -1;
      break;
    }
  }
  return cmp;
}

int s21_sub_same_signs(s21_big_decimal value1, s21_big_decimal value2,
                       s21_big_decimal *result) {
  int code = 0;
  int diff = 0;
  int borrow = 0;

  int cmp = s21_big_decimal_compare_abs(value1, value2);

  if (cmp == 0) {
    // Numbers are equal
    s21_big_decimal_null(result);
    result->sign = 0;
  } else {
    s21_big_decimal minuend = value1;
    s21_big_decimal subtrahend = value2;

    if (cmp < 0) {
      minuend = value2;
      subtrahend = value1;
      result->sign = (value1.sign == 0) ? 1 : 0;
    } else {
      result->sign = value1.sign;
    }

    for (int i = 0; i < BIG_DEC_BITS; i++) {
      int bit_min = s21_big_decimal_get_bit(minuend, i);
      int bit_sub = s21_big_decimal_get_bit(subtrahend, i);

      diff = bit_min - bit_sub - borrow;

      if (diff >= 0) {
        s21_big_decimal_set_bit(result, i, diff);
        borrow = 0;
      } else {
        s21_big_decimal_set_bit(result, i, diff + 2);
        borrow = 1;
      }
    }

    if (borrow != 0) {
      code = 1;  //
    }

    // Set the scale
    result->scale = minuend.scale;
  }

  return code;
}
