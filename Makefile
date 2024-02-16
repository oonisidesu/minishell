NAME := minishell

# libft
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

CFLAGS := -Wall -Wextra -Werror -I./include -I$(LIBFT_DIR) -O2
LDFLAGS := -L$(LIBFT_DIR)
LIBS := -lft -lreadline

SRCS := src/minishell.c src/parser/prompt.c src/parser/lexer.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

#%.o: %.c
#	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -j4 -C $(LIBFT_DIR)

.PHONY: clean fclean re

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
