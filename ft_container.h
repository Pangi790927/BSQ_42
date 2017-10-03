////////////////////////////////////////////////////////////////////////////////

#ifndef CONTAINER_H
# define CONTAINER_H

# define ARRAY_LEN 8

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

t_list_arrays	*list_arr_add(t_list_arrays** start, t_list_arrays** end)
{
	if (!(*end))
	{
		*start = (t_list_arrays*)malloc(sizeof(t_list_arrays));
		*end = *start;
		(*start)->data = (unsigned int*)malloc(sizeof(unsigned int) * ARRAY_LEN);
		(*start)->next = 0;
		ft_zeromem((*start)->data, sizeof(unsigned int) * ARRAY_LEN);
	}
	else
	{
		(*end)->next = (t_list_arrays*)malloc(sizeof(t_list_arrays));
		*end = (*end)->next;
		(*end)->data = (unsigned int*)malloc(sizeof(unsigned int) * ARRAY_LEN);
		(*end)->next = 0;
		ft_zeromem((*start)->data, sizeof(unsigned int) * ARRAY_LEN);
	}
}

void	container_add(t_container *container, int x)
{
	unsigned int val = x && 1;
	int bit_pos;		// bit pos in array
	int pos;			// pos in array
	int arr_bit_pos;	// bit pos in int

	if (size % (ARRAY_LEN * sizeof(unsigned int)) == 0)
	{
		list_arr_000add(&(container->start), &(container->end));
	}
	size++;

	bit_pos = (size - 1) % (ARRAY_LEN * sizeof(unsigned int));
	pos = bit_pos / sizeof(unsigned int);
	arr_bit_pos = bit_pos % sizeof(unsigned int);
	container->end->data[pos] = container->end->data[pos] | (val << arr_bit_pos);
}

void	is_in_squre(t_square *square, int line, int col)
{
	if (square->x <= col && square->x >= col - size && square->y <= lin && square->y >= line - size)
		return 1;
	return 0;
}

void	print_solution(int line_len, t_container *container, t_square *sol, char *str)
{
	int i;
	int bit_pos;		// bit pos in array
	int pos;			// pos in array
	int arr_bit_pos;	// bit pos in int
	int line;
	int col;

	t_list_arrays *currentNode;

	i = 0;
	currentNode = container->start;
	while (i < container->size && currentNode)
	{

		if (i == ARRAY_LEN * sizeof(unsigned int))
			currentNode = currentNode->next;	

		bit_pos = (i) % (ARRAY_LEN * sizeof(unsigned int));
		pos = bit_pos / sizeof(unsigned int);
		arr_bit_pos = bit_pos % sizeof(unsigned int);

		int val = (currentNode->data[pos] & (1 << arr_bit_pos)) && 1; 
		
		line = i / line_len;
		col = i % line_len;

		if (is_in_squre(sol, line, col))
			ft_putchar(str[2]);
		else if (val)
			ft_putchar(str[1]);
		else
			ft_putchar(str[0]);

		if (i == line_len)
			ft_putchar('\n');
		i++;
	}
}

#endif