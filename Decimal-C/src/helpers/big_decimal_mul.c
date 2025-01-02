#include "helpers.h"

void s21_big_decimal_mul(s21_big_decimal big_decimal_1,
                         s21_big_decimal big_decimal_2,
                         s21_big_decimal* result) {
  s21_big_decimal_null(result);

  // Main multiplication loop
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (big_decimal_1.bits[i] && big_decimal_2.bits[j]) {
        unsigned long long mul = (unsigned long long)big_decimal_1.bits[i] *
                                 (unsigned long long)big_decimal_2.bits[j];

        unsigned int k = i + j;

        // Add existing value and carry
        mul += result->bits[k];

        // Store lower 32 bits
        result->bits[k] = (unsigned int)(mul & 0xFFFFFFFF);

        // Propagate carry
        mul >>= 32;
        while (mul != 0) {
          k++;
          mul += result->bits[k];
          result->bits[k] = (unsigned int)(mul & 0xFFFFFFFF);
          mul >>= 32;
        }
      }
    }
  }

  // Set the sign of the result (XOR)
  result->sign = big_decimal_1.sign ^ big_decimal_2.sign;

  // Sum the scales
  result->scale = big_decimal_1.scale + big_decimal_2.scale;

  // Normalize by dividing by 10 without losing precision
  // while (s21_is_divisible_by_10(*result) && result->scale > 0) {
  //   s21_big_decimal_scale_down(result);
  // }
}
