#include <iostream>
#include "xutest.h"

int add(int a, int b) {
  return a + b;
}

TEST(test, add) {
  EXPECT_EQ(add(3, 4), 7);
  EXPECT_EQ(add(3, 4), 8);
}

TEST(test, add2) {
  EXPECT_EQ(add(3, 4), 7);
}

int main() {
  return RUN_ALL_TESTS();
}
