#include "helpers.h"

// Cдвиг битов мантиссы big_decimal на shift_value
void s21_shift_left(s21_big_decimal *value, int shift_value) {
#ifdef DEBUG_S21_HELPERS
  if (shift_value < 1 || shift_value > 32) {
    fprintf(stderr,
            "Error: Invalid shift value %d. Must be between 1 and 32.\n",
            shift_value);
  }
#endif

  unsigned memory = 0;
  for (int i = 0; i < 7; i++) {
    unsigned temp = value->bits[i];
    value->bits[i] <<= shift_value;
    value->bits[i] |= memory;
    memory = temp >> (32 - shift_value);
  }
}