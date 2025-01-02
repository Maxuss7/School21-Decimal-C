#include "helpers.h"

void s21_set_sign(s21_decimal *value, int sign_value) {
#ifdef DEBUG_S21_HELPERS
  if (sign_value < 0 || sign_value > 28) {
    fprintf(stderr, "Error: Invalid sign value %d. Must be between 0 and 28.\n",
            sign_value);
  }
#endif

  s21_set_bit(value, 127, sign_value);
}