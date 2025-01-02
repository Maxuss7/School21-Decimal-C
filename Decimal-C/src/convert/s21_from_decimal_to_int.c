#include "../helpers/helpers.h"
#include "../s21_decimal.h"

// Note: used INT_MIN and INT_MAN from <limits.h>

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  if (dst == NULL) {
    err = 1;  // incorrect parameter
  } else {
    int sign_bit = 0;
    s21_decimal buf = {{0, 0, 0, 0}};
    err = s21_truncate(src, &buf);
    if (!err) {
      sign_bit = s21_get_sign(buf);
    }

    if (!err &&
        (buf.bits[2] > 0 || buf.bits[1] > 0 ||
         (sign_bit == 0 && buf.bits[0] > INT_MAX) ||
         (sign_bit == 1 && buf.bits[0] > ((unsigned)abs(INT_MIN + 1) + 1)))) {
      err = 1;  // overflow
    } else if (!err && sign_bit == 0) {
      *dst = (int)buf.bits[0];
    } else if (!err) {  // if (!err && sign_bit == 1)
      *dst = (int)buf.bits[0] * -1;
    }
  }

  return err;
}