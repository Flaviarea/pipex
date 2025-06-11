NAME = pipex_bonus
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = pipex_bonus.c \
	utils_bonus.c \
	main_bonus.c \
	path_bonus.c \

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	@cc $(CFLAGS) -I . -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
