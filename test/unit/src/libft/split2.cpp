#include <gtest/gtest.h>

extern "C" {
#include "libft.h"
}

TEST(Split2, space_tab) {
  char** actual = ft_split2(" 	a bb	ccc", " \t");

  std::vector<const char*> expect = {"a", "bb", "ccc", NULL};

  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

TEST(Split2, empty) {
  char** actual = ft_split2(" 	  		  ", " 	");

  std::vector<const char*> expect = {NULL};

  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

TEST(Split2, odd) {
  char** actual = ft_split2("12345", "24680");

  std::vector<const char*> expect = {"1", "3", "5", NULL};

  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}

TEST(Split2, even) {
  char** actual = ft_split2("12345", "13579");

  std::vector<const char*> expect = {"2", "4", NULL};

  for (size_t i = 0; expect[i]; ++i) {
    EXPECT_STREQ(expect[i], actual[i]);
  }
}
