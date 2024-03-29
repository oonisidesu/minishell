#include <gtest/gtest.h>

extern "C"
{
#include "minishell.h"
#include "variable/env.h"
#include "variable/var.h"
#include "libft.h"
}

// setされた値がgetできることの確認
TEST(Variable, set_envp_and_get_envp)
{
  t_minishell minish;

  const char *expect[] = {"HOME=/home", "USER=me", "PATH=/usr/bin",
                          "ENV=", "ENV2=a=b=c", NULL};
  init_minishell(&minish);
  set_envp(&minish, expect);
  char **actual = get_envp(&minish);
  for (size_t i = 0; expect[i]; ++i)
  {
    // std::cout << expect[i] << " " << actual[i] << std::endl;
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

// nullをset、getできることの確認
TEST(Variable, null)
{
  t_minishell minish;

  const char *envp[] = {NULL};
  init_minishell(&minish);
  set_envp(&minish, envp);
  char **actual = get_envp(&minish);
  EXPECT_EQ(envp[0], actual[0]);
}

// SHELL変数が出てこないことの確認
TEST(Variable, minish_type)
{
  t_minishell minish;

  const char *envp[] = {"VAR3=abc", "VAR1=/home", NULL};
  init_minishell(&minish);
  add_or_update_var(&minish, "VAR3", "abc", VAR_SHELL);
  char **actual = get_envp(&minish);
  EXPECT_STRNE(envp[0], actual[0]);
}

// valにdoublequoteをつけてgetできることの確認
TEST(Variable, get_envp_double_quote)
{
  t_minishell minish;

  const char *envp[] = {"HOME=/home", "USER=me", "PATH=/usr/bin",
                        "ENV=", "ENV2=a=b=c", NULL};
  const char *expect[] = {"HOME=\"/home\"", "USER=\"me\"", "PATH=\"/usr/bin\"",
                          "ENV=\"\"", "ENV2=\"a=b=c\"", NULL};
  init_minishell(&minish);
  set_envp(&minish, envp);
  char **actual = get_envp_double_quote(&minish);
  for (size_t i = 0; expect[i]; ++i)
  {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}
