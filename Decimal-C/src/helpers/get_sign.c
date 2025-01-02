#include "helpers.h"

int s21_get_sign(s21_decimal value) { return s21_get_bit(value, 127); }