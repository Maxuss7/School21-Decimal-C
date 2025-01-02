#include "helpers.h"

void s21_set_bit(s21_decimal *value, int index, int bit_value) {
#ifdef DEBUG_S21_HELPERS
  if (index < 0 || index > 127)
    fprintf(stderr,
            "Error: Invalid bit index value %d. Must be between 0 and 127.\n",
            index);
  if (bit_value != 1 && bit_value != 0)
    fprintf(stderr, "Error: Invalid bit value %d. Must be 0 or 1.\n",
            bit_value);
#endif

  int array_index = index / 32;
  int bit_index = index % 32;
  if (bit_value) {
    value->bits[array_index] |= (1 << bit_index);
  } else {
    value->bits[array_index] &= ~(1 << bit_index);
  }
}
