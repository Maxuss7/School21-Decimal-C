#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  if (dst == NULL || s21_decimal_check(src) != 0) {
    err = 1;  // incorrect parameter
  } else {
    double res = 0;
    for (int i = 0; i < 96; i++) {
      if (s21_get_bit(src, i) == 1) {
        res = res + pow(2, i);
      }
    }
    res = res / pow(10, s21_get_scale(src));
    if (s21_get_sign(src) == 1) {
      res = -1 * res;
    }
    *dst = (float)res;
  }
  return err;
}