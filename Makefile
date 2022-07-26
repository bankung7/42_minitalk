NAME_SERVER = server
NAME_CLIENT = client

LIBFT_DIR = libft
LIBFT = libft/libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRCS = server.c client.c

OBJS = $(SRCS:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(NAME_SERVER).o $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "server ready"

$(NAME_CLIENT): $(NAME_CLIENT).o $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "client ready"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "libft ready"

clean:
	@make clean -C ./libft
	@$(RM) $(OBJS_SV) $(OBJS_CT)

fclean: clean
	@make fclean -C ./libft
	@$(RM) server client libft.a

re: fclean all

.PHONY: all clean fclean re
