NAME = bsq

SRC = bsq.c solver.c ft_list.c ft_lib_0.c container.c
CFLAGS = -Wall -Wextra -Werror -O2 
#-g -pg

all: ${NAME}

${NAME}: 
	gcc ${SRC} ${CFLAGS} -o ${NAME}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all