#include "../helpers/helpers.h"
#include "../s21_decimal.h"

// #define DEBUG_S21_FROM_FLOAT_TO_DECIMAL

#ifdef DEBUG_S21_FROM_FLOAT_TO_DECIMAL
void debug_print_decimal(s21_decimal value, char *comment);
#endif

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  // if (dst == NULL || !finite(src) || fabsf(src) > (float)pow(2, 96) - 1) {
  if (dst == NULL || isinf(src) || isnan(src) ||
      fabsf(src) > (float)pow(2, 96) - 1) {
    err = 1;
  } else {
    s21_decimal res = {{0, 0, 0, 0}};
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -src;
    }

    if (src == 0) {
      // keep res = {{0, 0, 0, 0}};
    } else if (src < (float)pow(10, -DEC_MAX_SCALE)) {
      // too small (0 < |x| < 1e-28)
      // set err = 1 and dst = res = {{0, 0, 0, 0}};
      err = 1;
      memcpy(dst, &res, sizeof(s21_decimal));
    } else {  // pow(10,-28) <= |x| <= pow(2,96)-1)

      char ssrc[12 + 1] = {'\0'};  // to save src like this: '7.922816e+28'
      sprintf(ssrc, "%.6e", src);
      ssrc[1] = ssrc[0];  // replace '.' by first digit
      ssrc[8] = '\0';     // replace 'e' by '\0'
      unsigned int m = strtol(ssrc + 1, NULL, 10);  // get 7 mantissa digits
      int exp = strtol(ssrc + 9, NULL, 10);  // get initial ssrc exp value
      exp = exp - 6;  // correct exp as we "multiplied" mantissa on 10^6

      err = s21_from_int_to_decimal(m, &res);  // set mantissa digits

      if (exp > 0) {
        // mantissa =* 10^exp
        for (int i = exp; i > 0; i--) s21_decimal_multiply_by_10(&res);
      } else if (exp <= 0 && exp >= -DEC_MAX_SCALE) {
        s21_set_scale(&res, abs(exp));
      } else if (exp < -DEC_MAX_SCALE) {  // exp has to be in range [-28-6, -28[
        // "shift right" mantissa digits to set scale in [0, 28] range
        res.bits[0] = round((double)res.bits[0] * pow(10, exp + DEC_MAX_SCALE));
        s21_set_scale(&res, DEC_MAX_SCALE);
      }
    }
    if (!err) s21_set_sign(&res, sign);
    if (!err) memcpy(dst, &res, sizeof(s21_decimal));
  }
  return err;
}

#ifdef DEBUG_S21_FROM_FLOAT_TO_DECIMAL
void debug_print_decimal(s21_decimal value, char *comment) {
  printf("DEBUG (%s): dec_value->bits'[3] [2] [1] [0]': '%X %X %X %X'  \n",
         comment, value.bits[3], value.bits[2], value.bits[1], value.bits[0]);

  float res_float = 0;
  s21_from_decimal_to_float(value, &res_float);
  printf("DEBUG (%s): res_float = %.6e\n", comment, res_float);

  fflush(NULL);
}
#endif
