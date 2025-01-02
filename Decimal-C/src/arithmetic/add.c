
#include "../helpers/helpers.h"
#include "../s21_decimal.h"
// #include "arithmetic.h"
// #include "../comparison/comparison.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;  // OK;

  // Получаем знаки
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  // Создаем big_decimal структуры
  s21_big_decimal big_value_1, big_value_2, big_result;
  s21_big_decimal_null(&big_value_1);
  s21_big_decimal_null(&big_value_2);
  s21_big_decimal_null(&big_result);

  // Переводим decimal в big_decimal
  s21_decimal_to_big_decimal(value_1, &big_value_1);
  s21_decimal_to_big_decimal(value_2, &big_value_2);

  // Нормализуем скейлы

  int big_scale = s21_normalize_big_decimal(&big_value_1, &big_value_2);
  big_result.scale = big_scale;

  // Создаем вспомогательные переменные для сравнения модулей
  s21_decimal value_1_abs = value_1;
  s21_decimal value_2_abs = value_2;
  s21_set_sign(&value_1_abs, 0);
  s21_set_sign(&value_2_abs, 0);

  // Если знаки одинаковые (оба положительные или оба отрицательные)
  if (sign1 == sign2) {
    s21_add_same_signs(big_value_1, big_value_2, &big_result);
    big_result.sign = sign1;
  } else {
    // Если знаки разные, нужно вычитать
    if (s21_is_greater_or_equal(value_1_abs, value_2_abs)) {
      s21_sub_same_signs(big_value_1, big_value_2, &big_result);
    } else {
      s21_sub_same_signs(big_value_2, big_value_1, &big_result);
    }
  }

  // s21_big_decimal_to_decimal(big_result, result);
  status = s21_big_to_decimal_with_bank_round(big_result, result);

  return status;
}
