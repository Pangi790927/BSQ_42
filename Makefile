NAME = bsq

SRC = bsq.c solver.c
CFLAGS = -Wall -Wextra -Werror -O3

all: ${NAME}

${NAME}: 
	gcc ${SRC} ${CFLAGS} -o ${NAME}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all