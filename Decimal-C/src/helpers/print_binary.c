#include "helpers.h"

#ifdef DEBUG_S21_HELPERS
// Функция для отладки
void s21_print_binary(int n) {
  int bits = 32;
  for (int i = bits - 1; i >= 0; i--) {
    int bit = (n >> i) & 1;
    printf("%d", bit);
  }
}
#endif
