#include "../helpers/helpers.h"
#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  int is_less_or_equal = !(s21_is_greater(value1, value2));
  return is_less_or_equal;
}