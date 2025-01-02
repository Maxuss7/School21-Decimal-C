#include "helpers.h"

#define ERR_DECIMAL_SCALE_NOT_IN_RANGE 1
#define ERR_DECIMAL_UNUSED_BITS_NOT_0 2

// check s21_decimal value:
// scale must be in [0,28] (bits[3]: bits 16..23)
// bits[3]: bits 0..15 and 24..30 must be 0
// return 0 if value passed the checks, <>0 if not passed
int s21_decimal_check(const s21_decimal value) {
  int err = 0;
  unsigned int scale = (value.bits[3] >> 16) & 0xFF;
  if (scale > 28) {
    err = ERR_DECIMAL_SCALE_NOT_IN_RANGE;
  } else if ((value.bits[3] & 0x7F00FFFF) != 0) {
    err = ERR_DECIMAL_UNUSED_BITS_NOT_0;
  }
  return err;
}