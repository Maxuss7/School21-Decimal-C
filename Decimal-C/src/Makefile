CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
TFLAGS= $(shell pkg-config --cflags check) $(shell pkg-config --libs check) -lpthread -lm
# TFLAGS= $(shell pkg-config --cflags --libs check)  
BUILD=./

DECIMAL_LIB=s21_decimal.a
DECIMAL_ALL_C=./arithmetic/*.c ./comparison/*.c ./convert/*.c ./others/*.c  ./helpers/*.c  


DECIMAL_ALL_H=./s21_decimal.h ./helpers/helpers.h 

TESTS_RUNNER=s21_decimal_tests_runner
TESTS_ALL_C=./tests/*.c
TESTS_ALL_H=./tests/s21_decimal_tests.h

PRJ_CODE_ALL=$(DECIMAL_ALL_C) $(DECIMAL_ALL_H) $(TESTS_ALL_C) $(TESTS_ALL_H)

VALGRIND=valgrind --tool=memcheck --leak-check=yes --quiet 

OS:=$(shell uname -s)
ifeq ($(OS), Linux)
# TFLAGS += -lpthread -lm -lsubunit -lrt 
TFLAGS += -lsubunit -lrt 
endif

all: test

$(DECIMAL_LIB): clean
	$(CC) $(CFLAGS) -c $(DECIMAL_ALL_C) 
	ar rcs $(BUILD)$(DECIMAL_LIB) ./*.o
	ar rcs $(BUILD)$(DECIMAL_LIB) ./*.o
	ranlib $(BUILD)$(DECIMAL_LIB) 
	rm -f ./*.o

test: clean clang $(DECIMAL_LIB)
	$(CC) $(CFLAGS) $(TESTS_ALL_C) $(BUILD)$(DECIMAL_LIB)  $(TFLAGS) -o $(BUILD)$(TESTS_RUNNER)
	$(BUILD)$(TESTS_RUNNER)

clean:
	rm -f $(BUILD)*.o $(BUILD)$(DECIMAL_LIB) $(BUILD)$(TESTS_RUNNER) \
		  $(BUILD)*.gcda $(BUILD)*.gcno $(BUILD)*.gcov
	rm -rf $(BUILD)report_lcov
	rm -rf $(BUILD)report_gcov


clang:
	cp ../materials/linters/.clang-format ./ 
	clang-format -i $(PRJ_CODE_ALL)
	clang-format -n $(PRJ_CODE_ALL)
	rm -f ./.clang-format

lcov_report:
	$(CC) $(CFLAGS) --coverage $(TESTS_ALL_C) $(DECIMAL_ALL_C) \
							$(TFLAGS) -o $(BUILD)$(TESTS_RUNNER)			
	$(BUILD)$(TESTS_RUNNER)

	rm -rf $(BUILD)report_lcov
	mkdir $(BUILD)report_lcov
	lcov -t "$(TESTS_RUNNER)" -c -d $(BUILD) \
					-o $(BUILD)report_lcov/$(TESTS_RUNNER)_report_lcov.info 
	genhtml -o $(BUILD)report_lcov $(BUILD)report_lcov/$(TESTS_RUNNER)_report_lcov.info
	open $(BUILD)report_lcov/index.html
	rm -f $(BUILD)*.gcda $(BUILD)*.gcno

gcov_report:
	$(CC) $(CFLAGS) --coverage $(TESTS_ALL_C) $(DECIMAL_ALL_C) \
							$(TFLAGS) -o $(BUILD)$(TESTS_RUNNER)			
	$(BUILD)$(TESTS_RUNNER)
	gcov -o  $(BUILD)*.gcno
	rm -rf $(BUILD)report_gcov
	mkdir $(BUILD)report_gcov
	gcovr -r $(BUILD) --html --html-details \
				-o $(BUILD)report_gcov/$(TESTS_RUNNER)_report_gcov.html
	open $(BUILD)report_gcov/$(TESTS_RUNNER)_report_gcov.html
	rm -f $(BUILD)*.gcda $(BUILD)*.gcno $(BUILD)*.gcov

valgrind:
	$(VALGRIND) $(BUILD)$(TESTS_RUNNER)


# cppcheck:
# 	cppcheck $(STRING).a tests/*c --enable=all --suppress=missingIncludeSystem

# OPEN_CMD = open
# ifeq ($(shell uname -s), Linux)
# OPEN_CMD = xdg-open
# endif

#.PHONY: all clean test s21_string.a

