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

  const char* expected = "abcd!@#123";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, nest_quote) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "'\"\"'\"''\"";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  const char* expected = "\"\"''";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, quote) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "'12$ENV1%&'abcd!'$ENV2'@#123'$ENV3''\"hello\"'";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  const char* expected = "12$ENV1%&abcd!$ENV2@#123$ENV3\"hello\"";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, double_quote) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "'12$ENV1%&'abcd!'$ENV2'@#123'$ENV3'\"'hello'\"";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  const char* expected = "12$ENV1%&abcd!$ENV2@#123$ENV3'hello'";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, special_param_0_9) {
  t_minishell minish;
  t_token tok;
  const char* argv[] = {"./minishell", NULL};

  init_minishell(&minish);
  minish.argc = 1;
  minish.argv = argv;

  std::string str = "abc$00$11$22$33$44$55$66$77$88$99123";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  const char* expected = "abc./minishell0123456789123";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, special_param_other) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);
  minish.status_code = 128;

  std::string str = "aaa$#$*$@$?$-$!aaa";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  const char* expected = "aaa01280aaa";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, special_param_in_quote_and_d_quote) {
  t_minishell minish;
  t_token tok;
  const char* argv[] = {"./minishell", NULL};

  init_minishell(&minish);
  minish.argc = 1;
  minish.argv = argv;

  std::string str = "'abc$00$11$22$33$44'\"$55$66$77$88$99123\"";
  tok.str = strdup(str.c_str());
  tok.len = str.size();

  const char* expected = "abc$00$11$22$33$4456789123";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}
