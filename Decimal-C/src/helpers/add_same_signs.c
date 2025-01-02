
#include "helpers.h"

int s21_add_same_signs(s21_big_decimal value1, s21_big_decimal value2,
                       s21_big_decimal *result) {
  int code = 0;
  int sum = 0;
  int carry = 0;

  if (value1.sign == 1 && value2.sign == 1) {
    result->sign = 1;
  }

  for (int i = 0; i < BIG_DEC_BITS; i++) {
    sum = s21_big_decimal_get_bit(value1, i) +
          s21_big_decimal_get_bit(value2, i) + carry;
    if (sum == 0) {  // 0  0
      s21_big_decimal_set_bit(result, i, 0);
      carry = 0;
    } else if (sum == 1) {  // 1 0
      s21_big_decimal_set_bit(result, i, 1);
      carry = 0;
    } else if (sum == 2) {  //  1 1
      s21_big_decimal_set_bit(result, i, 0);
      carry = 1;
    } else if (sum == 3) {
      s21_big_decimal_set_bit(result, i, 1);
      carry = 1;
    }
  }

  if (carry > 0) code = 1;

  return code;
}