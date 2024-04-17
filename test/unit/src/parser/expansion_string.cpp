#include <gtest/gtest.h>

extern "C" {
#include "libft.h"
#include "parser/expansion.h"
}

TEST(Expansion, push_exp_string1) {
  t_expansion exp;

  init_expansion(&exp, "abcdef", 3);

  push_exp_string(&exp, "xx", 0);
  push_exp_string(&exp, "1xx", 1);
  push_exp_string(&exp, "22xx", 2);
  push_exp_string(&exp, "333xx", 3);
  push_exp_string(&exp, "4444xx", 4);
  push_exp_string(&exp, "55555xx", 5);

  const char* expected = "122333444455555";

  EXPECT_STREQ(expected, exp.ret);
}

TEST(Expansion, push_exp_string2) {
  t_expansion exp;

  init_expansion(&exp, "abcdef", 3);

  push_exp_string(&exp, "12345678xx", 8);
  push_exp_string(&exp,
                  "123456789012345678901234567890123456789012345678901234"
                  "5678901234567890123456789012345678901234567890xx",
                  100);

  const char* expected =
      "1234567812345678901234567890123456789012345678901234567890123456789012"
      "34567890123456789012345678901234567890";

  EXPECT_STREQ(expected, exp.ret);
}

TEST(Expansion, add_exp_array) {
  t_expansion exp;
  char c;

  init_expansion(&exp, "abcdef", 3);

  for (int i = 0; i < 100; i++) {
    push_exp_string(&exp, "1234567890xx", i % 10);
    add_exp_array(&exp);
  }

  for (int i = 0; i < 100; i++) {
    char* expected = ft_substr("1234567890xx", 0, i % 10);
    EXPECT_STREQ(expected, exp.arr_ret[i]);
  }
}
