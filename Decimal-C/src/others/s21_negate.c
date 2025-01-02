#include "../helpers/helpers.h"
#include "../s21_decimal.h"

/* Возвращает результат умножения указанного Decimal на -1.*/
int s21_negate(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL || s21_decimal_check(value) != 0) {
    err = 1;
  } else {
    s21_set_sign(&value, s21_get_sign(value) == 0 ? 1 : 0);
    memcpy(result, &value, sizeof(s21_decimal));
  }
  return err;
}