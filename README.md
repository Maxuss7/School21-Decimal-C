# 💻 Decimal Implementation in C

**Description**:  
A library for high-precision arithmetic implemented in C. It includes support for arithmetic and comparison operations, type conversions, and rounding functionality.

---

### **Features**
- Supports up to 96-bit numbers with a scale (precision) indicator.
- Optimized for financial calculations.

---

### **Technologies Used**
![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
- Bit-level operations for high-precision arithmetic.
- Automated testing with the `Check` unit testing framework.
- _gcov_ and _lcov_ are used for code coverage analysis and visualization, ensuring comprehensive test coverage.

---

### **Usage**

#### **1. Clone the repository**
```bash
$ git clone https://github.com/yourusername/decimal-c-library.git
$ cd decimal-c-library/src
```

#### **2. Build the library**
Make sure you have a C compiler installed (e.g., GCC or Clang). Then run:
```bash
$ make s21_decimal.a
```

#### **3. Run tests**
To verify that the implementation works as expected, you can run the included test suite:
```bash
$ make test
```

#### **4. Include in your project**
To use the library in your project, include the `s21_decimal.h` header file and link the compiled library.

##### Example:
```c
#include "s21_decimal.h"
#include <stdio.h>

int main() {
    s21_decimal a, b, result;
    s21_from_int_to_decimal(10, &a);
    s21_from_int_to_decimal(20, &b);

    if (s21_add(a, b, &result) == 0) {
        printf("Addition result: ");
        s21_print_decimal(result);
    }

    return 0;
}
```

Compile and link:
```bash
$ gcc -o main main.c s21_decimal.a
$ ./main
```
