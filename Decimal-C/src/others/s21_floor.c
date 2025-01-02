#include "../helpers/helpers.h"
#include "../s21_decimal.h"

/* Округляет указанное Decimal число до ближайшего целого числа в сторону
 * отрицательной бесконечности.*/
int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL || s21_decimal_check(value) != 0) {
    err = 1;
  } else {
    s21_decimal res = {{0, 0, 0, 0}};
    int reminder_flag = 0;
    err = s21_truncate_and_get_reminder_info(value, &res, &reminder_flag, NULL);

    if (s21_get_sign(value) == 1 && reminder_flag != 0) {
      // set mantissa = mantissa + 1
      s21_decimal_mantissa_add_increment(&res, 1);
    }

    if (!err) memcpy(result, &res, sizeof(s21_decimal));
  }
  return err;
}