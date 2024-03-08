#include <gtest/gtest.h>

extern "C" {
#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
}

TEST(Expansion, word) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "abcd!@#123";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  char* expected = "abcd!@#123";
  char* actual = expand_str(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, quote) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "'12$ENV1%&'abcd!'$ENV2'@#123'$ENV3'";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  char* expected = "12$ENV1%&abcd!$ENV2@#123$ENV3";
  char* actual = expand_str(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}
