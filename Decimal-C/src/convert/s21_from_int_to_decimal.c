#include "../s21_decimal.h"

// Note: used INT_MIN and INT_MAN from <limits.h>

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err = 0;
  if (dst == NULL) {
    err = 1;
  } else {
    // "abs(INT_MIN)" may have 'undefined behaviour'
    // (UB). Usually "abs(INT_MIN) == INT_MIN" (!!!), still it depends on system
    // implementation. So, the code below escapes the UB case
    s21_decimal tdst = {
        {(src == INT_MIN ? (unsigned)abs(INT_MIN + 1) + 1 : (unsigned)abs(src)),
         0, 0, (src >= 0 ? 0 : 0x80000000)}};

    memcpy(dst, &tdst, sizeof(s21_decimal));
  }

  return err;
}