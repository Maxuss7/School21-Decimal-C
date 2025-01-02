#include "helpers.h"

void s21_set_scale(s21_decimal *value, int scale) {
#ifdef DEBUG_S21_HELPERS
  if (scale < 0 || scale > 28) {
    fprintf(stderr, "Error: Invalid scale %d. Must be between 0 and 28.\n",
            scale);
  }
#endif

  value->bits[3] &= ~(0xFF << 16);  // Очистка старого скейла
  value->bits[3] |= (scale << 16);  // Установление нового скейла
}