#include "../helpers/helpers.h"
#include "../s21_decimal.h"

/* Возвращает целые цифры указанного Decimal числа; любые дробные цифры
 * отбрасываются, включая конечные нули.*/
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int err = 0;
  err = s21_truncate_and_get_reminder_info(value, result, NULL, NULL);
  return err;
}

// reminder_flag = 1 if reminder != 0  else reminder_flag = 0
// reminder_first_digit : first digit of fractional part (after decimal point)
// e.g. reminder_first_digit = 5 for '0.5123' fractional part of number,
// reminder_first_digit = 0 for '0.05123'
int s21_truncate_and_get_reminder_info(s21_decimal value, s21_decimal *result,
                                       int *reminder_flag,
                                       int *reminder_first_digit) {
  int err = 0;
  if (result == NULL || s21_decimal_check(value) != 0) {
    err = 1;
  }

  unsigned long long buf = 0;
  unsigned long long rem = 0;
  int rem_flag = 0;
  int rem_first_digit = 0;
  unsigned int scale = s21_get_scale(value);
  s21_decimal res = {{0, 0, 0, 0}};
  if (!err) memcpy(&res, &value, sizeof(s21_decimal));

  if (!err && scale > 0) {  // if fractional digits exists
    // truncate fructional part and set scale = 0
    // for (int exp = scale; exp > 0; exp--) {
    for (unsigned int exp = 1; exp <= scale; exp++) {
      rem = 0;
      for (int i = 2; i >= 0; i--) {
        buf = (rem << 32) + res.bits[i];
        rem = buf % 10;
        res.bits[i] = buf / 10;
      }
      if (rem_flag != 1 && rem != 0) rem_flag = 1;
      if (exp == scale) rem_first_digit = rem;
    }
    s21_set_scale(&res, 0);
  }

  if (!err) {
    memcpy(result, &res, sizeof(s21_decimal));
    if (reminder_flag != NULL) *reminder_flag = rem_flag;
    if (reminder_first_digit != NULL) *reminder_first_digit = rem_first_digit;
  }
  return err;
}
