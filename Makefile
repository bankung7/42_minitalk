NAME = minitalk
NAME_SV = server
NAME_CT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS_DIR = srcs/
SRCS_SV = server.c
SRCS_CT = client.c

OBJS_DIR = objs/
OBJS_SV = $(addprefix $(OBJS_DIR), $(SRCS_SV:.c=.o))
OBJS_CT = $(addprefix $(OBJS_DIR), $(SRCS_CT:.c=.o))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_INC = -Ilibft/

all: $(NAME_SV) $(NAME_CT)

bonus: $(NAME_SV) $(NAME_CT)

$(NAME_SV): $(OBJS_SV) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "server is ready"

$(NAME_CT): $(OBJS_CT) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "client is ready"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $^ $(LIBFT_INC) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "libft is ready"

clean:
	@$(RM) $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "minitalk was cleaned"

fclean: clean
	@$(RM) $(NAME_SV) $(NAME_CT)
	@make fclean -C $(LIBFT_DIR)
	@echo "minitalk was fclean"

re: fclean all

.PHONY: all clean fclean re
