#include <gtest/gtest.h>

extern "C" {
#include "minishell.h"
#include "variable/env.h"
#include "variable/var.h"
}

// 追加
TEST(Variable, add) {
  t_minishell minish;
  const char* expect[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                          "ENV1=",      "ENV2=a=b=c", NULL};
  char** actual;

  init_minishell(&minish);
  add_or_update_var(&minish, "HOME", "/home", VAR_ENV);
  add_or_update_var(&minish, "USER", "me", VAR_ENV);
  add_or_update_var(&minish, "PATH", "/usr/bin", VAR_ENV);
  add_or_update_var(&minish, "ENV1", "", VAR_ENV);
  add_or_update_var(&minish, "ENV2", "a=b=c", VAR_ENV);
  actual = get_envp(&minish);
  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

// 更新
TEST(Variable, update) {
  t_minishell minish;
  const char* envp[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                        "ENV1=",      "ENV2=a=b=c", NULL};
  const char* expect[] = {"HOME=/home",  "USER=me",    "PATH=/usr/bin",
                          "ENV1=update", "ENV2=a=b=c", "ENV=add",
                          NULL};
  char** actual;

  init_minishell(&minish);
  set_envp(&minish, envp);
  add_or_update_var(&minish, "ENV1", "update", VAR_ENV);
  add_or_update_var(&minish, "ENV", "add", VAR_ENV);
  actual = get_envp(&minish);
  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

// 削除
TEST(Variable, del) {
  t_minishell minish;
  const char* envp[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                        "ENV1=",      "ENV2=a=b=c", NULL};
  const char* expect[] = {"HOME=/home", "USER=me",  "PATH=/usr/bin",
                          "ENV1=",      "ENV3=add", NULL};
  char** actual;

  init_minishell(&minish);
  set_envp(&minish, envp);
  del_var(&minish, "ENV");
  del_var(&minish, "1ENV");
  del_var(&minish, "ENV2");
  add_or_update_var(&minish, "ENV3", "add", VAR_ENV);
  actual = get_envp(&minish);
  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

// 取得
TEST(Variable, get) {
  t_minishell minish;

  const char* envp[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                        "ENV1=",      "ENV2=a=b=c", NULL};
  const char* expect[] = {"a=b=c", NULL};

  init_minishell(&minish);
  set_envp(&minish, envp);
  char* actual = get_var(&minish, "ENV2");
  char* actual1 = get_var(&minish, "ENV");
  EXPECT_STREQ(expect[0], actual);
  EXPECT_STREQ(expect[1], actual1);
}

TEST(Variable, is_var_declaration) {
  EXPECT_TRUE(is_var_declaration("AAA=123", 7));
  EXPECT_TRUE(is_var_declaration("A12=123", 7));
  EXPECT_TRUE(is_var_declaration("A12=132", 7));
  EXPECT_TRUE(is_var_declaration("_12=123", 7));
  EXPECT_TRUE(is_var_declaration("A_1=123", 7));
  EXPECT_TRUE(is_var_declaration("AAA=", 4));
  EXPECT_TRUE(is_var_declaration("A12=$AB", 7));
  EXPECT_TRUE(is_var_declaration("A12=@!$", 7));
  EXPECT_TRUE(is_var_declaration("A=0=1=2", 7));

  EXPECT_FALSE(is_var_declaration("A123", 4));
  EXPECT_FALSE(is_var_declaration("AAA=123", 3));
  EXPECT_FALSE(is_var_declaration("1AA=123", 7));
  EXPECT_FALSE(is_var_declaration("#AA=123", 7));
  EXPECT_FALSE(is_var_declaration("AA$=123", 7));
  EXPECT_FALSE(is_var_declaration("=123", 4));
}

TEST(Variable, divide_key_val1) {
  char** actual = divide_key_val("HOME=/home");
  const char* expected[] = {"HOME", "/home", NULL};
  for (size_t i = 0; expected[i]; ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
  }
}

TEST(Variable, divide_key_val2) {
  char** actual = divide_key_val("HOME=");
  const char* expected[] = {"HOME", "", NULL};
  for (size_t i = 0; expected[i]; ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
  }
}

TEST(Variable, divide_key_val3) {
  char** actual = divide_key_val("AA=1=2=3");
  const char* expected[] = {"AA", "1=2=3", NULL};
  for (size_t i = 0; expected[i]; ++i) {
    EXPECT_STREQ(expected[i], actual[i]);
  }
}

TEST(Variable, divide_key_val4) {
  char** actual = divide_key_val("ABC");

  EXPECT_EQ(NULL, actual);
}
