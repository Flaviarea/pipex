
NAME = pipex
CFLAGS = -Wall -Wextra -Werror -I include -I $(LIBFT_DIR)

SRC_DIR = srcs
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

REMOVE = rm -rf

SRCS = $(SRC_DIR)/pipex.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/main.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	cc $(CFLAGS) -I . -I $(LIBFT_DIR) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

