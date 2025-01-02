#include "../helpers/helpers.h"
#include "../s21_decimal.h"

/* Округляет Decimal до ближайшего целого числа. */
int s21_round(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL || s21_decimal_check(value) != 0) {
    err = 1;
  } else {
    s21_decimal res = {{0, 0, 0, 0}};
    int reminder_first_digit = 0;
    err = s21_truncate_and_get_reminder_info(value, &res, NULL,
                                             &reminder_first_digit);

    if (reminder_first_digit >= 5) {
      // set mantissa = mantissa + 1
      s21_decimal_mantissa_add_increment(&res, 1);
    }

    if (!err) memcpy(result, &res, sizeof(s21_decimal));
  }
  return err;
}

// add increment to mantissa of s21_decimal value
// the sign and scale of s21_decimal value are not changed/considered
// return 0 in case of "no mantissa overflow"
// or "mantissa overflow number" > 0 in case of the overflow
unsigned int s21_decimal_mantissa_add_increment(s21_decimal *value,
                                                unsigned int increment) {
  // set mantissa = mantissa + increment
  unsigned long long buf = 0;
  unsigned int carry = increment;
  for (int i = 0; i <= 2; i++) {
    buf = value->bits[i] + carry;
    value->bits[i] = buf & 0xFFFFFFFF;
    carry = ((buf >> 32) & 0xFFFFFFFF);
  }
  return carry;
}