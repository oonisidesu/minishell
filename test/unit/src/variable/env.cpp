#include <gtest/gtest.h>

extern "C" {
#include "minishell.h"
#include "variable/env.h"
}

// Demonstrate some basic assertions.
TEST(Variable, set_envp) {
  t_minishell minish;

  const char* expect[] = {"HOME=/home", "USER=me",    "PATH=/usr/bin",
                          "ENV1=",      "ENV2=a=b=c", NULL};

  set_envp(&minish, expect, VAR_ENV);
  char** actual = get_envp(&minish);

  for (size_t i = 0; expect[i]; ++i) {
    // std::cout << envp[i] << " " << actual[i] << std::endl;
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

TEST(Variable, null) {
  t_minishell minish;

  const char* envp[] = {NULL};

  set_envp(&minish, envp, VAR_ENV);
  // add_var(&minish.env, "VAR1", "111", VAR_SHELL);
  // add_var(&minish.env, "VAR2", NULL, VAR_SHELL);
  // add_var(&minish.env, "VAR3", "abc", VAR_ENV);
  // del_var(&minish.env, "VAR3");
  char** actual = get_envp(&minish);

  EXPECT_EQ(envp[0], actual[0]);
}

TEST(Variable, add_env) {
  t_minishell minish;

  const char* envp[] = {NULL};
  const char* expect[] = {"ENV1=env1", "ENV2=env2", NULL};

  set_envp(&minish, envp, VAR_ENV);
  // add_var(&minish.env, "ENV1", "env1", VAR_ENV);
  // add_var(&minish.env, "ENV2", "env2", VAR_ENV);

  char** actual = get_envp(&minish);

  for (size_t i = 0; expect[i]; ++i) {
    // std::cout << envp[i] << " " << actual[i] << std::endl;
    EXPECT_STREQ(expect[i], actual[i]);
  }
}
