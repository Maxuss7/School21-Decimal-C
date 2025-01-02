#include "helpers.h"

int s21_big_decimal_get_bit(s21_big_decimal value, int index) {
#ifdef DEBUG_S21_HELPERS
  if (index < 0 || index > 255)
    fprintf(stderr, "Error: Invalid bit index %d. Must be between 0 and 255.\n",
            index);
#endif

  int array_index = index / 32;
  int bit_index = index % 32;
  int bit = (value.bits[array_index] >> bit_index) & 1;
  return bit;
}