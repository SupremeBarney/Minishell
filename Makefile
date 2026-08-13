NAME = minishell
CC = cc

INC_DIR = .

CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR) -Ilibftprintf -g3 -O0
LDFLAGS = -Llibftprintf
READLINE = -lreadline -lncurses
LDLIBS  = -lftprintf $(READLINE)

LIBFT = libftprintf/libftprintf.a
LIBFT_SRC = $(wildcard libftprintf/*.c libftprintf/libft/*.c)

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT): $(LIBFT_SRC)
	$(MAKE) -C libftprintf

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libftprintf clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libftprintf fclean

re: fclean all

.PHONY: all clean fclean re
