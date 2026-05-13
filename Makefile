NAME = minishell
CC = cc

INC_DIR = .

CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR) -Ilibftprintf -g3 -O0
LDFLAGS = -Llibftprintf
LDLIBS  = -lftprintf

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

libftprintf:
	$(MAKE) -C libftprintf

$(NAME): libftprintf $(OBJ)
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

.PHONY: all clean fclean re libftprintf