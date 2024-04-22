#include <gtest/gtest.h>

extern "C" {
#include "libft.h"
#include "minishell.h"
#include "parser/lexer.h"
}

// Demonstrate some basic assertions.
TEST(Lexer, words) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup("ls -al file1.txt file2.txt");

  tokenize(&minish);

  std::vector<const char*> expected = {"ls", "-al", "file1.txt", "file2.txt",
                                       ""};
  std::vector<int> expected_kind = {1, 1, 1, 1, 2};

  std::vector<const char*> actual = {};
  std::vector<int> actual_kind = {};

  for (auto token = minish.token; token; token = token->next) {
    actual.push_back(strndup(token->str, token->len));
    actual_kind.push_back(token->kind);
  }

  ASSERT_EQ(expected.size(), actual.size());

  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
    EXPECT_EQ(expected_kind[i], actual_kind[i]);
  }
}

TEST(Lexer, pipe) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup(
      "> in1 < out1 ls -al|cat file1 file2>out1>out2>>att1<in1<in2 file3|ps "
      "-aux");

  tokenize(&minish);

  std::vector<const char*> expected = {
      ">",     "in1", "<",     "out1", "ls",   "-al",  "|",    "cat", "file1",
      "file2", ">",   "out1",  ">",    "out2", ">>",   "att1", "<",   "in1",
      "<",     "in2", "file3", "|",    "ps",   "-aux", ""};
  std::vector<int> expected_kind = {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0,
                                    1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 2};

  std::vector<const char*> actual = {};
  std::vector<int> actual_kind = {};

  for (auto token = minish.token; token; token = token->next) {
    actual.push_back(strndup(token->str, token->len));
    actual_kind.push_back(token->kind);
  }

  ASSERT_EQ(expected.size(), actual.size());

  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
    EXPECT_EQ(expected_kind[i], actual_kind[i]);
  }
}

TEST(Lexer, quote_and_d_quote) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup("echo \"ls | cat\"'$PWD'\" > \"' << '");

  tokenize(&minish);

  std::vector<const char*> expected = {"echo",
                                       "\"ls | cat\"'$PWD'\" > \"' << '", ""};
  std::vector<int> expected_kind = {1, 1, 2};

  std::vector<const char*> actual = {};
  std::vector<int> actual_kind = {};

  for (auto token = minish.token; token; token = token->next) {
    actual.push_back(strndup(token->str, token->len));
    actual_kind.push_back(token->kind);
  }

  ASSERT_EQ(expected.size(), actual.size());

  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
    EXPECT_EQ(expected_kind[i], actual_kind[i]);
  }
}

TEST(Lexer, nest_quote) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup("\" ' ' \" '\"' \"'\"");

  tokenize(&minish);

  std::vector<const char*> expected = {"\" ' ' \"", "'\"'", "\"'\"", ""};

  std::vector<int> expected_kind = {1, 1, 1, 2};

  std::vector<const char*> actual = {};
  std::vector<int> actual_kind = {};

  for (auto token = minish.token; token; token = token->next) {
    actual.push_back(strndup(token->str, token->len));
    actual_kind.push_back(token->kind);
  }

  ASSERT_EQ(expected.size(), actual.size());

  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
    EXPECT_EQ(expected_kind[i], actual_kind[i]);
  }
}

TEST(Lexer, only_space) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup("     \t   ");

  tokenize(&minish);

  std::vector<const char*> expected = {""};

  std::vector<int> expected_kind = {2};

  std::vector<const char*> actual = {};
  std::vector<int> actual_kind = {};

  for (auto token = minish.token; token; token = token->next) {
    actual.push_back(strndup(token->str, token->len));
    actual_kind.push_back(token->kind);
  }

  ASSERT_EQ(expected.size(), actual.size());

  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
    EXPECT_EQ(expected_kind[i], actual_kind[i]);
  }
}

TEST(Lexer, donot_close_quote) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup("echo '");

  tokenize(&minish);

  ASSERT_EQ(ERR_SYNTAX, minish.error_kind);
}

TEST(Lexer, donot_close_d_quote) {
  t_minishell minish;
  init_minishell(&minish);
  minish.line = ft_strdup("echo \"aaa 'bbb' ccc");

  tokenize(&minish);

  ASSERT_EQ(ERR_SYNTAX, minish.error_kind);
}
