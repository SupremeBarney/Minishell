NAME = libftprintf.a
LIBFT = libft/libft.a
CC = cc
INC_DIR = .
CFLAGS = -Wall -Wextra -Werror -I${INC_DIR} -Ilibft
SRC = ft_printf.c \
outils.c
OBJ = $(SRC:.c=.o)

all: ${NAME}
	
$(NAME): $(OBJ) 
	$(MAKE) -C libft 
	cp $(LIBFT) $(NAME) 
	ar rcs $(NAME) $(OBJ)
	
clean:
	rm -f *.o
	$(MAKE) -C libft clean

fclean: clean
	rm -f ${NAME}
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
