#include "helpers.h"

#ifdef DEBUG_S21_HELPERS
// Функция для отладки
void s21_print_decimal(s21_decimal *value) {
  for (int i = 3; i >= 0; i--) {
    s21_print_binary(value->bits[i]);
    printf("\n");
  }
  printf("\n");
}
#endif