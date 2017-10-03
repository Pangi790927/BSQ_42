#ifndef SOLVER_H
# define SOLVER_H

#include "square.h"
#include "container.h"

enum {NO_ERROR, ERROR};

typedef struct	s_map
{
	int line_count;
	int line_lenght;
	int error;

	char empty;
	char full;
	char fill;

	t_square square;
	t_container container;
}				t_map;

t_map	*solver_solve(int fd, t_map *map);

#endif