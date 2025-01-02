#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "./../s21_decimal.h"

// #define DEBUG_S21_HELPERS

#ifdef DEBUG_S21_HELPERS
void s21_print_binary(int n);
void s21_print_decimal(s21_decimal *value);
void s21_print_big_decimal(s21_big_decimal *value);
#endif

int s21_get_bit(s21_decimal value, int index);
void s21_set_bit(s21_decimal *value, int index, int bit_value);
int s21_big_decimal_get_bit(s21_big_decimal value, int index);
void s21_big_decimal_set_bit(s21_big_decimal *value, int index, int bit_value);
void s21_shift_left(s21_big_decimal *value, int shift_value);

int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
int s21_normalize_big_decimal(s21_big_decimal *value1, s21_big_decimal *value2);
int s21_normalize_decimal(s21_decimal *value1, s21_decimal *value2);
void s21_big_decimal_multiply_by_10(s21_big_decimal *value);
void s21_decimal_multiply_by_10(s21_decimal *value);
void s21_big_decimal_null(s21_big_decimal *value);
void s21_big_decimal_mul(s21_big_decimal big_decimal_1,
                         s21_big_decimal big_decimal_2,
                         s21_big_decimal *result);

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign_value);
int s21_is_zero_decimal(s21_decimal *value);
int s21_is_0_decimal(s21_decimal value);
int s21_is_0_big_decimal(s21_big_decimal value);
int s21_decimal_check(const s21_decimal value);

void s21_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result);
void s21_decimal_to_big_decimal(s21_decimal value, s21_big_decimal *result);
int s21_is_equal_bits_decimal(s21_decimal value1, s21_decimal value2);

int s21_add_same_signs(s21_big_decimal value1, s21_big_decimal value2,
                       s21_big_decimal *result);
int s21_sub_same_signs(s21_big_decimal value1, s21_big_decimal value2,
                       s21_big_decimal *result);

//============================================================================
// others -> helpers
//============================================================================

// reminder_flag = 1 if reminder != 0  else reminder_flag = 0
// reminder_first_digit : first digit of fractional part (after decimal point)
// e.g. reminder_first_digit = 5 for '0.5123' fractional part of number,
// reminder_first_digit = 0 for '0.05123'
int s21_truncate_and_get_reminder_info(s21_decimal value, s21_decimal *result,
                                       int *reminder_flag,
                                       int *reminder_first_digit);

// add increment to mantissa of s21_decimal value
// the sign and scale of s21_decimal value are not changed/considered
// return 0 in case of "no mantissa overflow"
// or "mantissa overflow number" > 0 in case of the overflow
unsigned int s21_decimal_mantissa_add_increment(s21_decimal *value,
                                                unsigned int increment);

//============================================================================
// arithmetic -> helpers
//============================================================================

void s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);

/* Convert s21_big_decimal number to s21_decimal number with bank rounding
Return codes:
0 - OK
1 - TOO_BIG_NUM    (> (pow(2,96)-1))
2 - TOO_SMALL_NUM  (< -(pow(2,96)-1)) */
int s21_big_to_decimal_with_bank_round(s21_big_decimal value,
                                       s21_decimal *result);

void s21_big_decimal_copy(s21_big_decimal value, s21_big_decimal *result);

// return 1 if mantissa_value_1 > mantissa_value_2, else return 0
int s21_big_v1_mantissa_is_greater(s21_big_decimal value_1,
                                   s21_big_decimal value_2);

void s21_big_mantissa_mul_10_exp(s21_big_decimal *value, unsigned int exp);

// return reminder of the division
int s21_big_mantissa_div_10_exp(s21_big_decimal *value, unsigned int exp);

// add increment to mantissa of s21_big_decimal value
// the sign and scale of s21_big_decimal value are not changed/considered
// return 0 in case of "no mantissa overflow"
// or "mantissa overflow number" > 0 in case of the overflow
unsigned int s21_big_mantissa_add_increment(s21_big_decimal *value,
                                            unsigned int increment);

#endif
