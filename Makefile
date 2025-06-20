NAME = pipex
BONUS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MANDATORY_SRCS = pipex_mandatory.c \
	utils.c \
	main_mandatory.c \

BONUS_SRCS = pipex_bonus.c \
	main_bonus.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(MANDATORY_OBJS)
	@cc $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LIBFT)

bonus: $(BONUS_OBJS)
	@cc $(CFLAGS) -o $(BONUS) $(BONUS_OBJS) $(LIBFT)

%.o: %.c
	@cc $(CFLAGS) -I . -c $< -o $@

clean:
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

