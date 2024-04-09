NAME := minishell

UNAME := $(shell uname)

# libft
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
# readline
READLINE_TAR_GZ := readline-8.2.tar.gz
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
	src/parser/token.c src/parser/lexer.c \
	src/parser/parser.c src/parser/parser_utils.c src/parser/parser_redirect.c src/parser/parser_declare.c src/parser/parser_command.c \
	src/parser/prompt.c src/parser/node.c src/parser/expansion.c \
	src/parser/heredoc_input.c src/parser/heredoc_output.c src/parser/heredoc_utils.c \
	src/variable/env.c src/variable/env_util1.c src/variable/env_util2.c src/variable/var.c \
	src/exec/exec.c src/exec/find_path.c src/exec/pipe.c src/exec/redirect.c src/exec/ft_strsignal.c \
	src/exec/process_exec.c src/exec/process_wait.c \
	src/builtin/builtin.c src/builtin/builtin_echo.c src/builtin/builtin_cd.c src/builtin/builtin_pwd.c src/builtin/builtin_export.c \
	src/builtin/builtin_unset.c src/builtin/builtin_env.c src/builtin/builtin_exit.c src/builtin/builtin_exit_print.c src/builtin/builtin_var.c \
  	src/signal/signal.c \
	src/utils/utils.c src/utils/minishell_error.c
OBJS := $(SRCS:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(READLINE) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -j4 -C $(LIBFT_DIR)

$(READLINE_TAR_GZ):
	curl -O ftp://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz

$(READLINE): $(READLINE_TAR_GZ)
	tar xvzf readline-8.2.tar.gz
	cd $(READLINE_DIR) && ./configure && $(MAKE) -j4


.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) -r $(READLINE_DIR)

.PHONY: re
re: fclean all

# test
.PHONY: test
test: unit_test e2e_test

.PHONY: unit_test
unit_test: $(READLINE) $(LIBFT)
	cd test/unit && \
	cmake -S . -B build && cmake --build build &&  cd build && ctest

.PHONY: e2e_test
e2e_test: $(NAME) $(e2e_clean)
	cd test/e2e && ./run_e2e.sh

.PHONY: e2e_clean
e2e_clean:
	$(RM) test/e2e/out/*.out
	$(RM) test/e2e/out/*.diff
