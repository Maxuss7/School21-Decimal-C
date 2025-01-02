#include "helpers.h"

int s21_get_scale(s21_decimal value) {
  int scale = (value.bits[3] >> 16) & 0xFF;
  return scale;
}