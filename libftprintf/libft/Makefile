NAME = libft.a
CC = cc
INC_DIR = .
CFLAGS = -Wall -Wextra -Werror -I${INC_DIR}
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}
	
%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@
	
clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
