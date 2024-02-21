NAME := minishell

# libft
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
# readline
READLINE_DIR := ./readline-8.2
READLINE := $(READLINE_DIR)/libreadline.a

INCLUDES := -I./include -I$(LIBFT_DIR) -I$(READLINE_DIR)
CFLAGS := -Wall -Wextra -Werror -O0 -g
LDFLAGS := -L$(LIBFT_DIR) -L$(READLINE_DIR)
LIBS := -lft -lreadline -lhistory -ltermcap

SRCS := src/main.c src/minishell.c src/parser/prompt.c src/parser/lexer.c src/parser/parser.c src/variable/env.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(READLINE)
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
