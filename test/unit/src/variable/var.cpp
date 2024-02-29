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
  init_minishell(&minish);
  add_or_update_var(&minish, "HOME", "/home", VAR_ENV);
  add_or_update_var(&minish, "USER", "me", VAR_ENV);
  add_or_update_var(&minish, "PATH", "/usr/bin", VAR_ENV);
  add_or_update_var(&minish, "ENV1", "", VAR_ENV);
  add_or_update_var(&minish, "ENV2", "a=b=c", VAR_ENV);
  char** actual = get_envp(&minish);
  for (size_t i = 0; expect[i] ; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

// 更新
TEST(Variable, update) {
  t_minishell minish;

  const char* expect[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                          "ENV1=",      "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, expect);
  add_or_update_var(&minish, "ENV1", "update", VAR_ENV);
  char** actual = get_envp(&minish);

  for (size_t i = 0; expect[i] ; ++i) {
    if (i == 3) {
      EXPECT_STRNE(expect[i], actual[i]);
    } else {
      EXPECT_STREQ(expect[i], actual[i]);
    }
  }
}

// 削除
TEST(Variable, del) {
  t_minishell minish;

  const char* expect[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                          "ENV1=",      "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, expect);
  del_var(&minish, "ENV2");
  add_or_update_var(&minish, "ENV3", "add", VAR_ENV);
  char** actual = get_envp(&minish);
  for (size_t i = 0; expect[i] ; ++i) {
    if (i == 4) {
      EXPECT_STRNE(expect[i], actual[i]);
    } else {
      EXPECT_STREQ(expect[i], actual[i]);
    }
  }
}

// 取得
TEST(Variable, get) {
  t_minishell minish;

  const char* expect[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                          "ENV1=",      "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, expect);
  char* actual = get_var(&minish, "ENV2");
  EXPECT_STREQ("a=b=c", actual);
}