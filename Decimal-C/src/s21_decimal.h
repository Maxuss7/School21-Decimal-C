#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEC_BITS 128
#define BIG_DEC_BITS 256
#define DEC_MAX_SCALE 28

// Error codes
#define FALSE 0
#define TRUE 1
#define TOO_BIG_NUM 1
#define TOO_SMALL_NUM 2
#define DIVISION_BY_ZERO 3
#define OK 0
#define CONVERTATION_ERROR 1
#define CALCULATION_ERROR 1

/*
Двоичное представление s21_decimal состоит из
1-разрядного знака, 96-разрядного целого числа и коэффициента масштабирования,
используемого для деления целого числа и указания того, какая его часть
является десятичной дробью. Коэффициент масштабирования неявно равен числу 10,
возведенному в степень в диапазоне от 0 до 28.
s21_decimal реализовано в виде четырехэлементного массива 32-разрядных целых
чисел без знака (unsigned int bits[4];).

bits[0], bits[1], и bits[2] содержат младшие, средние и старшие 32 бита
96-разрядного целого числа соответственно.

bits[3] содержит коэффициент масштабирования и знак и состоит
из следующих частей:
 - Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
 - Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
   указывает степень 10 для разделения целого числа.
 - Биты с 24 по 30 не используются и должны быть равны нулю.
 - Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.

Битовое представление различает отрицательные и положительные нули.
Эти значения считаем эквивалентными во всех операциях.

MAX_S21_DECIMAL: 79228162514264337593543950335 (29 decimal digits)
*/
typedef struct {
  unsigned int bits[4];
} s21_decimal;

// Временный тип для арифметики
typedef struct {
  unsigned int sign;
  unsigned int scale;
  unsigned int bits[8];
} s21_big_decimal;

// arithmetic

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// comparison

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// convert

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// others

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);

// Возвращает целые цифры указанного s21_decimal числа;
// любые дробные цифры отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);

// Возвращает результат умножения указанного s21_decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

#endif