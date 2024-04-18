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

TEST(Expansion, split_and_join_var) {
  t_expansion exp;
  char c;

  init_expansion(&exp, "123456789012345678901234567890", 30);

  push_exp_string(&exp, "1234567890xx", 10);
  join_var(&exp, "abc", 2);
  split_and_join_var(&exp, "'a   bb		  ccc dddd'   	", 2);
  split_and_join_var(&exp, "	  e ff  ", 2);
  split_and_join_var(&exp, " g hh", 2);
  push_exp_string(&exp, "1234567890xx", 10);

  EXPECT_STREQ("1234567890abc'a", exp.arr_ret[0]);
  EXPECT_STREQ("bb", exp.arr_ret[1]);
  EXPECT_STREQ("ccc", exp.arr_ret[2]);
  EXPECT_STREQ("dddd'", exp.arr_ret[3]);
  EXPECT_STREQ("e", exp.arr_ret[4]);
  EXPECT_STREQ("ff", exp.arr_ret[5]);
  EXPECT_STREQ("g", exp.arr_ret[6]);
  EXPECT_STREQ("hh1234567890", exp.arr_ret[7]);
}
