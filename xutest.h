#ifndef XUTEST_H
#define XUTEST_H

#include <stdio.h>
#include <string.h>
/**
 * @brief a simple unit testing
 */
#define EXPECT(a, comm, b) { \
  if (!((a) comm (b))) \
    expectPrintf(__FILE__, __LINE__, "(" #a ")" #comm "(" #b ")"); \
}

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)

#define TEST(a, b) \
	void a##_##b(); \
	__attribute__((constructor)) \
	void register_##a##_##b() { \
  	  add_test(a##_##b, #a "." #b); \
	} \
	void a##_##b()

#define COLOR(msg, show, code) "\033[" #show ";" #code "m" msg "\033[0m"
#define RED(msg) COLOR(msg, 1, 31)
#define GREEN(msg) COLOR(msg, 1, 32)
#define YELLOW(msg) COLOR(msg, 1, 33)
#define BLUE(msg) COLOR(msg, 1, 34)

bool err_exist;
void expectPrintf(const char* file_name, int line_no, const char* msg) {
  printf(YELLOW("            FILE: %s  LINE: %d : Failure:\n"), file_name, line_no);
  printf(YELLOW("            EXPECTED: %s\n"), msg);
  err_exist = true;
}

struct TestData {
  void (*func)();
  char* func_name;
} func_arr[100];
int func_cnt = 0;

void add_test(void (*func)(), const char* func_name) {
  func_arr[func_cnt].func = func;
  func_arr[func_cnt].func_name = strdup(func_name);
  func_cnt++;
  return;
}

int RUN_ALL_TESTS() {
  printf(BLUE("[==========]") " Runing %d test cases.\n", func_cnt);
  for (int i = 0; i < func_cnt; ++i) {
    err_exist = false;
    printf(GREEN("[   RUN    ]") " %s\n", func_arr[i].func_name);
    func_arr[i].func();
    if (err_exist) {
      printf(RED("[   FAILED ]") " %s\n", func_arr[i].func_name);
    } else {
      printf(GREEN("[   OK     ]") " %s\n", func_arr[i].func_name);
    }
  }
  printf(BLUE("[==========]") " %d test cases done.\n", func_cnt);
  return 0;
}

#endif
