#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// the better practise is to define the header file and include, instead of directly the code
#include "lib.c"

// Very small test helpers
int failed = 0;
// #define is untyped, purely TEXT substitutions (commonly for macros)
#define TEST(name) void name()
#define RUN_TEST(name) printf("\n\033[1m%s\n\033[0m", #name); name()
#define ASSERT(expr) if (!(expr)) { \
  failed = 1; \
  printf("\033[0;31mFAIL: %s\n\033[0m", #expr); \
} else { \
  printf("\033[0;32mPASS: %s\n\033[0m", #expr); \
}
#define ASSERT_STR_EQ(str1, str2) { \
  ASSERT(strcmp(str1, str2) == 0); \
  if (failed) { \
    printf("%s doesn't equal to %s\n", str1, str2); \
  } \
}
// End of test helpers

TEST(test_add) {
  ASSERT(add(1, 2) == 3);
  ASSERT(add(0, 0) == 0);
  ASSERT(add(-1, -1) == -2);
}

TEST(test_string_assert) {
  ASSERT_STR_EQ("hello", "hello");
}

// probably fail
TEST(test_concat) {
  char *result = my_strcat("hi", "ya");
  // if used immediately probably wont have error
  // but if there's something in between
  // printf("result: %s\n", result);
  // there's also a address of stack memory associated with local variable 'buffer' returned [-Wreturn-stack-address]
  ASSERT_STR_EQ(result, "hiya");
}

TEST(test_concat1) {
  char result[5] = {0};
  my_strcat1(result, "hi", "ya");
  ASSERT_STR_EQ(result, "hiya")
}

TEST(test_concat_better1) {
  char result[5] = {0};
  // array decay to pointer
  // once we pass in an array, it becomes a pointer inside the called function
  // once that happened, there’s no way to recover the original size using sizeof(buffer) or pointer dereferencing (inside the function).
  my_strcat_better1(result, 5, "hi", "yaaaaaaa");
  ASSERT_STR_EQ(result, "hiya");
}

TEST(test_concat_heap) {
  char *result = my_strcat_heap("hi", "ya");
  ASSERT_STR_EQ(result, "hiya");
  // caller needs to free heap memory
  // easily missed
  free(result);
}

TEST(test_fizzbuzz) {
  char buffer[100] = {0};
  generate_fizzbuzz(buffer, 100, 5);
  ASSERT_STR_EQ(buffer, "1, 2, Fizz, 4, Buzz.");
}

int main() {
  // Add a `RUN_TEST` line for each test function
  // RUN_TEST(test_add);
  // RUN_TEST(test_string_assert);
  // RUN_TEST(test_concat);
  // RUN_TEST(test_concat1);
  // RUN_TEST(test_concat_better1);
  // RUN_TEST(test_concat_heap);
  RUN_TEST(test_fizzbuzz);
  return failed;
}
