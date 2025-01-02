#include "helpers.h"

#ifdef DEBUG_S21_HELPERS
void s21_print_big_decimal(s21_big_decimal *value) {
  for (int i = 7; i >= 0; i--) {
    s21_print_binary(value->bits[i]);
    printf("\n");
  }
}
#endif
