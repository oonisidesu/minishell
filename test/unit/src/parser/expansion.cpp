#include <gtest/gtest.h>

extern "C" {
#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "variable/env.h"
}

TEST(Expansion, word) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "abcd!@#123";
  tok.str = str.c_str();
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
  tok.str = str.c_str();
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
  tok.str = str.c_str();
  tok.len = str.size();

  const char* expected = "12$ENV1%&abcd!$ENV2@#123$ENV3\"hello\"";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, double_quote) {
  t_minishell minish;
  t_token tok;

  init_minishell(&minish);

  std::string str = "\"12abc\"\"\"\"'hello'\"";
  tok.str = str.c_str();
  tok.len = str.size();

  const char* expected = "12abc'hello'";
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
  tok.str = str.c_str();
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
  tok.str = str.c_str();
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
  tok.str = str.c_str();
  tok.len = str.size();

  const char* expected = "abc$00$11$22$33$4456789123";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

TEST(Expansion, variable) {
  t_minishell minish;
  t_token tok;

  const char* envp[] = {"HOME=/home", "USER=me",    "PATH=/bin:/usr/bin",
                        "ENV=",       "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, envp);

  std::string str = "12$PATH%\"$HOME\"ABC$XXX%$$\"1$\"abc'$ENV'$ENV$ENV2";
  tok.str = str.c_str();
  tok.len = str.size();

  const char* expected = "12/bin:/usr/bin%/homeABC%$$1$abc$ENVa=b=c";
  char* actual = expand(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

// heredocの終端文字列は変数展開しない
TEST(Expansion, expand_delimiter) {
  t_minishell minish;
  t_token tok;

  const char* envp[] = {"HOME=/home", "USER=me",    "PATH=/bin:/usr/bin",
                        "ENV=",       "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, envp);

  std::string str = "12' '\" \"$HOME\"'a'\"'\"b\"'$?$$'\"\"'\"''\"";
  tok.str = str.c_str();
  tok.len = str.size();

  const char* expected = "12  $HOME'a'\"b\"$?$$\"\"''";
  char* actual = expand_delimiter(&minish, &tok);

  EXPECT_STREQ(expected, actual);
}

// heredoc内ではquote、d-quoteは解釈しない
TEST(Expansion, expand_heredoc) {
  t_minishell minish;
  t_token tok;

  const char* envp[] = {"HOME=/home", "USER=me",    "PATH=/bin:/usr/bin",
                        "ENV=",       "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, envp);
  minish.status_code = 120;

  std::string str = "12' '\" \"$HOME\"'a'\"'\"b\"'$?$$'\"\"'\"''\"";

  const char* expected = "12' '\" \"/home\"'a'\"'\"b\"'120$$'\"\"'\"''\"";
  char* actual = expand_heredoc(&minish, str.c_str());

  EXPECT_STREQ(expected, actual);
}
