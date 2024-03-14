NAME := minishell

UNAME := $(shell uname)

# libft
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
# readline
READLINE_DIR := ./readline-8.2
READLINE := $(READLINE_DIR)/libreadline.a

INCLUDES := -I./include -I$(LIBFT_DIR) -I$(READLINE_DIR)
CFLAGS := -Wall -Wextra -Werror -O0 -g -DREADLINE_LIBRARY -DRL_LIBRARY_VERSION='"8.2"'
LDFLAGS := -L$(LIBFT_DIR) -L$(READLINE_DIR)

ifeq ($(UNAME), Linux) # Linux
LIBS := -lft -lreadline -lhistory -ltinfo
endif
ifeq ($(UNAME), Darwin) # Mac OS
LIBS := -lft -lreadline -lhistory -ltermcap
endif


SRCS := src/main.c src/minishell.c \
	src/parser/prompt.c src/parser/lexer.c src/parser/parser.c src/parser/node.c src/parser/expansion.c \
	src/variable/env.c src/variable/var.c \
	src/exec/exec.c src/exec/find_path.c src/exec/pipe.c src/exec/process.c src/exec/redirect.c src/exec/ft_strsignal.c \
	src/builtin/builtin.c src/builtin/builtin_echo.c src/builtin/builtin_cd.c src/builtin/builtin_pwd.c src/builtin/builtin_export.c \
	src/builtin/builtin_unset.c src/builtin/builtin_env.c src/builtin/builtin_exit.c src/builtin/builtin_var.c \
  	src/signal/signal.c \
	src/utils/utils.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(READLINE) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -j4 -C $(LIBFT_DIR)

$(READLINE):
	curl -O ftp://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar xvzf readline-8.2.tar.gz
	cd $(READLINE_DIR) && ./configure && $(MAKE) -j4


.PHONY: clean fclean re

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) -r $(READLINE_DIR)
	$(RM) readline-8.2.tar.gz

re: fclean all

# test
.PHONY: unit_test e2e_test e2e_clean

unit_test: $(READLINE) $(LIBFT)
	cd test/unit && \
	cmake -S . -B build && cmake --build build &&  cd build && ctest

e2e_test: $(NAME) $(e2e_clean)
	cd test/e2e && ./run_e2e.sh

e2e_clean:
	$(RM) test/e2e/out/*.out
	$(RM) test/e2e/out/*.diff
