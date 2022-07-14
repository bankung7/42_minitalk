NAME = server

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRC_SV = ./server.c

SRC_CT = ./client.c

OBJS_SV = $(SRC_SV:.c=.o)

OBJS_CT = $(SRC_CT:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_SV) $(OBJS_CT)
	make -C ./libft
	cp libft/libftprintf.a libft.a
	$(CC) $(CFLAGS) $(OBJS_SV) libft.a -o server
	$(CC) $(CFLAGS) $(OBJS_CT) libft.a -o client

clean:
	make clean -C ./libft
	$(RM) $(OBJS_SV) $(OBJS_CT)

fclean: clean
	make fclean -C ./libft
	$(RM) server client libft.a

re: fclean

.PHONY: all clean fclean re server client