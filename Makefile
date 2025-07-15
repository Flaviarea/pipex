NAME = pipex
BONUS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror -I include -I $(LIBFT_DIR)

SRC_DIR = srcs
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MANDATORY_SRCS = $(SRC_DIR)/pipex_mandatory.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/main_mandatory.c

BONUS_SRCS = $(SRC_DIR)/pipex_bonus.c \
	$(SRC_DIR)/main_bonus.c \
	$(SRC_DIR)/utils.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(MANDATORY_OBJS)
	@cc $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LIBFT)

bonus: $(LIBFT) $(BONUS_OBJS)
	@cc $(CFLAGS) -o $(BONUS) $(BONUS_OBJS) $(LIBFT)

%.o: %.c
	cc $(CFLAGS) -I . -I $(LIBFT_DIR) -c $< -o $@

clean:
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

