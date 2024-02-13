NAME := minishell
CFLAGS := -Wall -Wextra -Werror -Iinclude
SRCS := src/minishell.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

#%.o: %.c
#	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean fclean re

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
