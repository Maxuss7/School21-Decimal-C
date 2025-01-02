#include "../helpers/helpers.h"
#include "../s21_decimal.h"

// #define DEBUG_S21_DIV
#ifdef DEBUG_S21_DIV
void debug_print_s21_div(s21_big_decimal val, char *comment);
#endif

/* Деление
Функции возвращают код ошибки:
0 — OK;
1 — число слишком велико или равно бесконечности;
2 — число слишком мало или равно отрицательной бесконечности;
3 — деление на 0.

Уточнение про числа, не вмещающиеся в мантиссу:
При получении чисел, не вмещающихся в мантиссу при арифметических операциях,
используй банковское округление (например,
79,228,162,514,264,337,593,543,950,335 — 0.6 =
79,228,162,514,264,337,593,543,950,334).
*/
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  if (result == NULL || s21_decimal_check(value_1) != 0 ||
      s21_decimal_check(value_2) != 0) {
    err = -1;  // incorrect parameter
  } else if (s21_is_0_decimal(value_2) != 0) {
    err = 3;  // DIVISION_BY_ZERO
  } else {
    s21_big_decimal a = {0, 0, {0}};
    s21_big_decimal b = {0, 0, {0}};
    s21_big_decimal c = {0, 0, {0}};
    s21_decimal_to_big_decimal(value_1, &a);
    s21_decimal_to_big_decimal(value_2, &b);

    s21_big_div(a, b, &c);  // culculate a/b=c
    err = s21_big_to_decimal_with_bank_round(c, result);
  }
  return err;
}

void s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result) {
  s21_big_decimal_null(result);

  s21_big_decimal a, b, c, buf_a, buf_c;  // culculate a/b=c
  s21_big_decimal_copy(value_1, &a);
  s21_big_decimal_copy(value_2, &b);
  s21_big_decimal_null(&c);

  // debug_print_s21_div(value_1, "s21_big_div 1 v1=>");
  // debug_print_s21_div(value_2, "s21_big_div 1 v2=>");

  s21_big_mantissa_mul_10_exp(&a, b.scale);
  b.scale = 0;

  // debug_print_s21_div(a, "s21_big_div 2 a=>");
  // debug_print_s21_div(b, "s21_big_div 2 b=>");

  unsigned int scale_c = 0;
  int is_div_completed = 0;

  do {
    s21_big_decimal_null(&buf_a);
    s21_big_decimal_null(&buf_c);
    int i = BIG_DEC_BITS - 1;  // 255

    // for (; i >= 0 && s21_big_decimal_get_bit(a, i) != 1; i--); // error!
    while (s21_big_decimal_get_bit(a, i) != 1 && i > 0) {
      i--;
    }

    for (; i >= 0; i--) {
      s21_shift_left(&buf_a, 1);
      s21_big_decimal_set_bit(&buf_a, 0, s21_big_decimal_get_bit(a, i));

      // int debug_flag1 = 1;
      // if (debug_flag1 == 1) {
      //   debug_print_s21_div(buf_a, "s21_big_div 3 buf_a=>");
      //   debug_flag1 = 0;
      // }
      // if (i == 0) debug_print_s21_div(b, "s21_big_div 3 b=>");

      if (!(s21_big_v1_mantissa_is_greater(b, buf_a))) {
        // debug_print_s21_div(buf_a, "!!!!!!!!!!!!!! s21_big_div 3 buf_a=>");

        s21_big_decimal_set_bit(&buf_c, i, 1);

        // debug_print_s21_div(buf_a, "s21_big_div 3 buf_a=>");
        // debug_print_s21_div(buf_c, "s21_big_div 3 buf_c=>");

        s21_sub_same_signs(buf_a, b, &buf_a);

        // debug_print_s21_div(buf_a, "!!!!!!!!!!!!!! s21_big_div 3 buf_a-b=>");
      }
    }

    s21_add_same_signs(c, buf_c, &c);

    // debug_print_s21_div(buf_a, "s21_big_div 4 buf_a=");
    // debug_print_s21_div(a, "s21_big_div 5 a=");
    // debug_print_s21_div(buf_c, "s21_big_div 3 buf_c=");
    // debug_print_s21_div(c, "s21_big_div 7 c=");

    if (s21_is_0_big_decimal(buf_a) || c.bits[3] > 9 ||
        scale_c > DEC_MAX_SCALE) {
      is_div_completed = 1;
    } else {  // process fractionl part of 'c'

      // debug_print_s21_div(buf_a, "s21_big_div buf_a_rem=>");

      s21_big_decimal_copy(buf_a, &a);
      s21_big_mantissa_mul_10_exp(&a, 1);
      s21_big_mantissa_mul_10_exp(&c, 1);
      scale_c++;
    }
  } while (is_div_completed == 0);

  c.sign = a.sign ^ b.sign;
  c.scale = scale_c + value_1.scale;
  memcpy(result, &c, sizeof(s21_big_decimal));

  // debug_print_s21_div(*result, "s21_big_div 8 result=");
}

/* Convert s21_big_decimal number to s21_decimal number with bank rounding
Return codes:
0 - OK
1 - TOO_BIG_NUM    (> (pow(2,96)-1))
2 - TOO_SMALL_NUM  (< -(pow(2,96)-1)) */
int s21_big_to_decimal_with_bank_round(s21_big_decimal value,
                                       s21_decimal *result) {
  int err = 0;
  // s21_decimal res = {0,0,0,0};
  s21_big_decimal val = {0, 0, {0}};
  s21_big_decimal_copy(value, &val);
  int reminder = 0;

#ifdef DEBUG_S21_DIV
  debug_print_s21_div(value, "round before");
  printf("DEBUG (round before): val.scale = %d\n", val.scale);
  fflush(NULL);
#endif

  while ((!s21_is_0_big_decimal(val) && val.scale > DEC_MAX_SCALE) ||
         (val.scale > 0 && (val.bits[7] || val.bits[6] || val.bits[5] ||
                            val.bits[4] || val.bits[3]))) {
    reminder = s21_big_mantissa_div_10_exp(&val, 1);
    val.scale--;
    // bank round
    if (reminder > 5 ||
        (reminder == 5 && s21_big_decimal_get_bit(val, 0) == 0)) {
      s21_big_mantissa_add_increment(&val, 1);
    }
  }

  if (s21_is_0_big_decimal(val)) {
    val.scale = 0;
  }

#ifdef DEBUG_S21_DIV
  debug_print_s21_div(value, "round after ");
  printf("DEBUG (round after ): val.scale = %d\n", val.scale);
  fflush(NULL);
#endif

  // check MIN-MAX range
  if (val.bits[7] || val.bits[6] || val.bits[5] || val.bits[4] || val.bits[3]) {
    err = (value.sign == 0 ? TOO_BIG_NUM : TOO_SMALL_NUM);
  } else {  // convert to s21_decimal
    s21_big_decimal_to_decimal(val, result);
  }

  return err;
}

void s21_big_decimal_copy(s21_big_decimal value, s21_big_decimal *result) {
  result->sign = value.sign;
  result->scale = value.scale;
  for (int i = 0; i < 8; i++) {
    result->bits[i] = value.bits[i];
  }
}

// return 1 if mantissa_value_1 > mantissa_value_2, else return 0
int s21_big_v1_mantissa_is_greater(s21_big_decimal value_1,
                                   s21_big_decimal value_2) {
  int res = 0;
  for (int i = 7; i >= 0 && res == 0; i--) {
    if ((unsigned int)(value_1.bits[i]) > (unsigned int)(value_2.bits[i])) {
      res = 1;
    }
  }
  return res;
}

void s21_big_mantissa_mul_10_exp(s21_big_decimal *value, unsigned int exp) {
  while (exp--) {
    unsigned long long buf = 0;
    for (int i = 0; i < 8; i++) {
      buf = (unsigned long long)value->bits[i] * 10 + buf;
      value->bits[i] = (unsigned int)(buf & 0xFFFFFFFF);
      buf = ((buf >> 32) & 0xFFFFFFFF);
    }
  }
}

int s21_big_mantissa_div_10_exp(s21_big_decimal *value, unsigned int exp) {
  unsigned long long remainder = 0;
  unsigned long long buf = 0;
  while (exp--) {
    remainder = 0;
    for (int i = 7; i >= 0; i--) {
      buf = (remainder << 32) + value->bits[i];
      remainder = buf % 10;
      value->bits[i] = buf / 10;
    }
  }
  return (int)remainder;
}

// add increment to mantissa of s21_big_decimal value
// the sign and scale of s21_big_decimal value are not changed/considered
// return 0 in case of "no mantissa overflow"
// or "mantissa overflow number" > 0 in case of the overflow
unsigned int s21_big_mantissa_add_increment(s21_big_decimal *value,
                                            unsigned int increment) {
  // set mantissa = mantissa + increment
  unsigned long long buf = 0;
  unsigned int carry = increment;
  for (int i = 0; i <= 7; i++) {
    buf = value->bits[i] + carry;
    value->bits[i] = buf & 0xFFFFFFFF;
    carry = ((buf >> 32) & 0xFFFFFFFF);
  }
  return carry;
}

#ifdef DEBUG_S21_DIV
void debug_print_s21_div(s21_big_decimal val, char *comment) {
  printf(
      "DEBUG (%s): val.bits'[7]..[0]': '%X "
      "%X %X %X %X %X %X %X'\n",
      comment, val.bits[7], val.bits[6], val.bits[5], val.bits[4], val.bits[3],
      val.bits[2], val.bits[1], val.bits[0]);
  fflush(NULL);
}
#endif