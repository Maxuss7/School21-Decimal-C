
#include "../helpers/helpers.h"
#include "./s21_decimal_tests.h"

// Положительные целые
START_TEST(sub_pos_pos_1) {
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
  // Также должна быть проверка на возвращаемый код
}
END_TEST

START_TEST(sub_pos_pos_2) {
  s21_decimal d2 = {{24, 7, 4, 0}};
  s21_decimal d1 = {{40, 7, 6, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{16, 0, 2, 0}};

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_pos_3) {
  s21_decimal d1 = {{100, 6, 30, 0}};
  s21_decimal d2 = {{100, 10, 2, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 4294967292, 27, 0}};

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_pos_4) {
  s21_decimal d1 = {{121, 12, 126, 0}};
  s21_decimal d2 = {{123, 24, 123, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFF3, 0x2, 0}};

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_pos_5) {
  s21_decimal d1 = {{0, 0, 0, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_pos_6) {
  s21_decimal d1 = {{123000, 100, 200, 0}};
  s21_decimal d2 = {{1000, 100, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{122000, 0, 199, 0}};
  s21_set_sign(&expected, 0);

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_neg_1) {
  s21_decimal d1 = {{123000, 100, 200, 0}};
  s21_decimal d2 = {{1000, 100, 1, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{122000, 0, 199, 0}};

  // Set the signs of d1 and d2 to negative
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  // The expected result should be negative
  s21_set_sign(&expected, 1);

  s21_sub(d1, d2, &res);

  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_neg_2) {
  // Initialize decimals
  s21_decimal d1 = {{5000, 0, 0, 0}};  // -50.00
  s21_decimal d2 = {{5000, 0, 0, 0}};  // -50.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs (both negative)
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // Expected result is 0

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_neg_3) {
  // Initialize decimals
  s21_decimal d1 = {{5000, 0, 0, 0}};   // -50.00
  s21_decimal d2 = {{15000, 0, 0, 0}};  // -150.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs (both negative)
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{10000, 0, 0, 0}};  // 100.00

  // Set expected scale and sign
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 0);  // Positive

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_neg_4) {
  // Initialize decimals
  s21_decimal d1 = {{15000, 0, 0, 0}};  // -150.00
  s21_decimal d2 = {{5000, 0, 0, 0}};   // -50.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs (both negative)
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{10000, 0, 0, 0}};  // -100.00

  // Set expected scale and sign
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_neg_5) {
  // Initialize decimals
  s21_decimal d1 = {{123456789, 0, 0, 0}};  // -1234.56789
  s21_decimal d2 = {{10000, 0, 0, 0}};      // -100.00

  // Set scales
  s21_set_scale(&d1, 5);  // Scale 5
  s21_set_scale(&d2, 2);  // Scale 2

  // Set signs (both negative)
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result calculation:
  // -1234.56789 - (-100.00) = -1234.56789 + 100.00 = -1134.56789

  s21_decimal expected = {{113456789, 0, 0, 0}};  // -1134.56789
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_neg_6) {
  // Initialize decimals
  s21_decimal d1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // -Maximum value
  s21_decimal d2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // -Maximum value

  // Set scales
  s21_set_scale(&d1, 0);
  s21_set_scale(&d2, 0);

  // Set signs (both negative)
  s21_set_sign(&d1, 1);
  s21_set_sign(&d2, 1);

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // Expected result is 0

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_neg_1) {
  // Инициализация чисел
  s21_decimal d1 = {{5000, 0, 0, 0}};  // 50.00
  s21_decimal d2 = {{2000, 0, 0, 0}};  // -20.00

  // Установка масштаба
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Установка знаков
  s21_set_sign(&d1, 0);  // Положительное
  s21_set_sign(&d2, 1);  // Отрицательное

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{7000, 0, 0, 0}};  // 70.00

  // Установка ожидаемого масштаба и знака
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 0);  // Положительное

  // Выполнение вычитания
  int ret = s21_sub(d1, d2, &res);

  // Проверка на отсутствие ошибок
  ck_assert_int_eq(ret, 0);

  // Проверка результата
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_neg_2) {
  // Инициализация чисел
  s21_decimal d1 = {{10000, 0, 0, 0}};  // 100.00
  s21_decimal d2 = {{50000, 0, 0, 0}};  // -500.00

  // Установка масштаба
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Установка знаков
  s21_set_sign(&d1, 0);  // Положительное
  s21_set_sign(&d2, 1);  // Отрицательное

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{60000, 0, 0, 0}};  // 600.00

  // Установка ожидаемого масштаба и знака
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 0);  // Положительное

  // Выполнение вычитания
  int ret = s21_sub(d1, d2, &res);

  // Проверка на отсутствие ошибок
  ck_assert_int_eq(ret, 0);

  // Проверка результата
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_neg_3) {
  // Инициализация чисел
  s21_decimal d1 = {{1234567, 0, 0, 0}};  // 12.34567
  s21_decimal d2 = {{10000, 0, 0, 0}};    // -100.00

  // Установка масштабов
  s21_set_scale(&d1, 5);  // Масштаб 5
  s21_set_scale(&d2, 2);  // Масштаб 2

  // Установка знаков
  s21_set_sign(&d1, 0);  // Положительное
  s21_set_sign(&d2, 1);  // Отрицательное

  s21_decimal res = {{0, 0, 0, 0}};

  // Ожидаемый результат: 112.34567
  s21_decimal expected = {{11234567, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 0);  // Положительное

  // Выполнение вычитания
  int ret = s21_sub(d1, d2, &res);

  // Проверка на отсутствие ошибок
  ck_assert_int_eq(ret, 0);

  // Проверка результата
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_pos_neg_4) {
  // Инициализация чисел
  s21_decimal d1 = {{0, 0, 0, 0}};     // 0.00
  s21_decimal d2 = {{5000, 0, 0, 0}};  // -50.00

  // Установка масштабов
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Установка знаков
  s21_set_sign(&d1, 0);  // Положительное
  s21_set_sign(&d2, 1);  // Отрицательное

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{5000, 0, 0, 0}};  // 50.00

  // Установка ожидаемого масштаба и знака
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 0);  // Положительное

  // Выполнение вычитания
  int ret = s21_sub(d1, d2, &res);

  // Проверка на отсутствие ошибок
  ck_assert_int_eq(ret, 0);

  // Проверка результата
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_pos_1) {
  // Initialize numbers
  s21_decimal d1 = {{2000, 0, 0, 0}};  // -20.00
  s21_decimal d2 = {{5000, 0, 0, 0}};  // 50.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{7000, 0, 0, 0}};  // -70.00

  // Set expected scale and sign
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_pos_2) {
  // Initialize numbers
  s21_decimal d1 = {{10000, 0, 0, 0}};  // -100.00
  s21_decimal d2 = {{50000, 0, 0, 0}};  // 500.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal expected = {{60000, 0, 0, 0}};  // -600.00

  // Set expected scale and sign
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_pos_3) {
  // Initialize numbers
  s21_decimal d1 = {{50000, 0, 0, 0}};   // -500.00
  s21_decimal d2 = {{100000, 0, 0, 0}};  // 1000.00

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: -1500.00
  s21_decimal expected = {{150000, 0, 0, 0}};  // -1500.00
  s21_set_scale(&expected, 2);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_neg_pos_4) {
  // Initialize numbers
  s21_decimal d1 = {{1234567, 0, 0, 0}};  // -12.34567
  s21_decimal d2 = {{10000, 0, 0, 0}};    // 100.00

  // Set scales
  s21_set_scale(&d1, 5);  // Scale 5
  s21_set_scale(&d2, 2);  // Scale 2

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: -112.34567
  s21_decimal expected = {{11234567, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales1) {
  // Initialize numbers
  s21_decimal d1 = {{123456789, 0, 0, 0}};  // 1234.56789
  s21_decimal d2 = {{10000, 0, 0, 0}};      // 100.00

  // Set scales
  s21_set_scale(&d1, 5);  // Scale 5
  s21_set_scale(&d2, 2);  // Scale 2

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: 1134.56789
  s21_decimal expected = {{113456789, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 0);  // Positive

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales2) {
  // Initialize numbers
  s21_decimal d1 = {{5000, 0, 0, 0}};    // 50.00
  s21_decimal d2 = {{123456, 0, 0, 0}};  // -1.23456

  // Set scales
  s21_set_scale(&d1, 2);
  s21_set_scale(&d2, 5);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 1);  // Negative

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: 51.23456
  s21_decimal expected = {{5123456, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 0);  // Positive

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales3) {
  // Initialize numbers
  s21_decimal d1 = {{123456, 0, 0, 0}};  // -1.23456
  s21_decimal d2 = {{5000, 0, 0, 0}};    // 50.00

  // Set scales
  s21_set_scale(&d1, 5);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: -51.23456
  s21_decimal expected = {{5123456, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales4) {
  // Initialize numbers
  s21_decimal d1 = {{987654321, 0, 0, 0}};  // -9.87654321
  s21_decimal d2 = {{12345, 0, 0, 0}};      // -0.12345

  // Set scales
  s21_set_scale(&d1, 8);
  s21_set_scale(&d2, 5);

  // Set signs
  s21_set_sign(&d1, 1);  // Negative
  s21_set_sign(&d2, 1);  // Negative

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: -9.75309321
  s21_decimal expected = {{975309321, 0, 0, 0}};
  s21_set_scale(&expected, 8);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales5) {
  // Initialize numbers
  s21_decimal d1 = {{0, 0, 0, 0}};          // 0.000
  s21_decimal d2 = {{123456789, 0, 0, 0}};  // 123.456789

  // Set scales
  s21_set_scale(&d1, 3);
  s21_set_scale(&d2, 6);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: -123.456789
  s21_decimal expected = {{123456789, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales6) {
  // Initialize numbers
  s21_decimal d1 = {{123456789, 0, 0, 0}};  // 123.456789
  s21_decimal d2 = {{0, 0, 0, 0}};          // 0.00

  // Set scales
  s21_set_scale(&d1, 6);
  s21_set_scale(&d2, 2);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: 123.456789
  s21_decimal expected = {{123456789, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  s21_set_sign(&expected, 0);  // Positive

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales7) {
  // Initialize numbers
  s21_decimal d1 = {{100000, 0, 0, 0}};  // 1.00000
  s21_decimal d2 = {{1, 0, 0, 0}};       // 0.00001

  // Set scales
  s21_set_scale(&d1, 5);
  s21_set_scale(&d2, 5);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: 0.99999
  s21_decimal expected = {{99999, 0, 0, 0}};
  s21_set_scale(&expected, 5);
  s21_set_sign(&expected, 0);  // Positive

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales8) {
  // Initialize numbers
  s21_decimal d1 = {{1, 0, 0, 0}};  // 0.0000000000000000000000000001
  s21_decimal d2 = {{2, 0, 0, 0}};  // 0.0000000000000000000000000002

  // Set scales
  s21_set_scale(&d1, 28);
  s21_set_scale(&d2, 28);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: -0.0000000000000000000000000001
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_set_scale(&expected, 28);
  s21_set_sign(&expected, 1);  // Negative

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(sub_different_scales9) {
  // Initialize numbers
  s21_decimal d1 = {{1000000000, 0, 0, 0}};  // 10.00000000
  s21_decimal d2 = {{1, 0, 0, 0}};           // 0.1

  // Set scales
  s21_set_scale(&d1, 8);
  s21_set_scale(&d2, 1);

  // Set signs
  s21_set_sign(&d1, 0);  // Positive
  s21_set_sign(&d2, 0);  // Positive

  s21_decimal res = {{0, 0, 0, 0}};

  // Expected result: 9.90000000
  s21_decimal expected = {{990000000, 0, 0, 0}};
  s21_set_scale(&expected, 8);
  s21_set_sign(&expected, 0);  // Positive

  // Perform subtraction
  int ret = s21_sub(d1, d2, &res);

  // Normalize scales if your implementation reduces scale
  // s21_normalize_scale(&res);

  // Check that no error occurred
  ck_assert_int_eq(ret, 0);

  // Validate the result
  ck_assert_mem_eq(&res, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *get_suite_s21_sub(void) {
  Suite *s = suite_create("\033[44m-=s21_sub=-\033[0m");
  TCase *tc = tcase_create("s21_sub_tc");

  tcase_add_test(tc, sub_pos_pos_1);
  tcase_add_test(tc, sub_pos_pos_2);
  tcase_add_test(tc, sub_pos_pos_3);
  tcase_add_test(tc, sub_pos_pos_4);
  tcase_add_test(tc, sub_pos_pos_5);
  tcase_add_test(tc, sub_pos_pos_6);
  //   tcase_sub_test(tc, sub_pos_pos_7);
  //   tcase_sub_test(tc, sub_pos_pos_8);
  //   tcase_sub_test(tc, sub_pos_pos_9);
  //   tcase_sub_test(tc, sub_pos_pos_10);

  tcase_add_test(tc, sub_neg_neg_1);
  tcase_add_test(tc, sub_neg_neg_2);
  tcase_add_test(tc, sub_neg_neg_3);
  tcase_add_test(tc, sub_neg_neg_4);
  tcase_add_test(tc, sub_neg_neg_5);
  tcase_add_test(tc, sub_neg_neg_6);
  //   tcase_sub_test(tc, sub_neg_neg_7);
  //   tcase_sub_test(tc, sub_neg_neg_8);
  //   tcase_sub_test(tc, sub_neg_neg_9);
  //   tcase_sub_test(tc, sub_neg_neg_10);

  tcase_add_test(tc, sub_pos_neg_1);
  tcase_add_test(tc, sub_pos_neg_2);
  tcase_add_test(tc, sub_pos_neg_3);
  tcase_add_test(tc, sub_pos_neg_4);

  tcase_add_test(tc, sub_neg_pos_1);
  tcase_add_test(tc, sub_neg_pos_2);
  tcase_add_test(tc, sub_neg_pos_3);
  tcase_add_test(tc, sub_neg_pos_4);

  tcase_add_test(tc, sub_different_scales1);
  tcase_add_test(tc, sub_different_scales2);
  tcase_add_test(tc, sub_different_scales3);
  tcase_add_test(tc, sub_different_scales4);
  tcase_add_test(tc, sub_different_scales5);
  tcase_add_test(tc, sub_different_scales6);
  tcase_add_test(tc, sub_different_scales7);
  tcase_add_test(tc, sub_different_scales8);
  tcase_add_test(tc, sub_different_scales9);
  //   tcase_sub_test(tc, sub_decimals_different_scales10);

  suite_add_tcase(s, tc);
  return s;
}
