NAME = server client

INC = libft/inc/

LIBFT = $(LIBFT_DIR)/libftprintf.a
LIBFT_DIR = libft

CC = gcc

CFLAGS = -Wall -Wextra -Werror
NPD_FLAG = --no-print-directory

RM = rm -rf

SRCS = server.c client.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) $(NPD_FLAG)
	@$(CC) $(CFLAGS) $(LIBFT) objs/server.o -o server
	@$(CC) $(CFLAGS) $(LIBFT) objs/client.o -o client
	@echo "server and client are ready"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I/$(INC) -c $^ -o $@

clean:
	@make clean -C $(LIBFT_DIR) $(NPD_FLAG)
	@$(RM) $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR) $(NPD_FLAG)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re