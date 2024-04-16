#include <gtest/gtest.h>

extern "C" {
#include "parser/expansion.h"
}

TEST(String, 1) {
  t_expansion exp;

  init_expansion(&exp, "abcdef", 3);

  push_string(&exp, "1xx", 1);
  push_string(&exp, "23xx", 2);
  push_string(&exp, "456xx", 3);

  const char* expected = "123456";

  EXPECT_STREQ(expected, exp.ret);
}

TEST(String, 2) {
  t_expansion exp;

  init_expansion(&exp, "abcdef", 3);

  push_string(&exp, "1234567890xx", 10);
  push_string(&exp,
              "123456789012345678901234567890123456789012345678901234"
              "5678901234567890123456789012345678901234567890xx",
              100);

  const char* expected =
      "123456789012345678901234567890123456789012345678901234567890123456789012"
      "34567890123456789012345678901234567890";

  EXPECT_STREQ(expected, exp.ret);
}
