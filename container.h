////////////////////////////////////////////////////////////////////////////////

#ifndef CONTAINER_H
# define CONTAINER_H

# define ARRAY_LEN 8
# define BITS_IN_BYTE 8

#include "square.h"

typedef struct	s_list_arrays
{
	unsigned int *data;
	struct s_list_arrays* next;
}				t_list_arrays;

typedef struct	s_container
{
	t_list_arrays *start;
	t_list_arrays *end;
	int size;
}				t_container;

void			container_free_mem(t_container *container);
void			container_init(t_container *container);
void			container_add(t_container *container, int x);
void			print_solution(int line_len, t_container *container, t_square *sol, char *str);

#endif