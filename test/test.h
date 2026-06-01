#ifndef TEST_H
#define TEST_H
#include <stdio.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define TEST(fn) { \
  printf("TEST\t%s ... ", #fn); \
  if ((fn)()) { \
    printf("ok\n"); \
  } else { \
    printf("FAILED\n"); \
    ++exit_code; \
  } \
}

#define SETUP_RUNNER() int exit_code = 0
#define TESTS_RESULT (exit_code)
extern int exit_code;

#endif
