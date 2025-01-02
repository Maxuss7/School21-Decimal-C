#include "helpers.h"

// Обертка чтобы умножить децимал на 10
// (для тестов пригодилось)
void s21_decimal_multiply_by_10(s21_decimal *value) {
  s21_big_decimal bd1;
  s21_decimal_to_big_decimal(*value, &bd1);
  s21_big_decimal_multiply_by_10(&bd1);
  s21_big_decimal_to_decimal(bd1, value);
}