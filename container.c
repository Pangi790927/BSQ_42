#include "container.h"

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"

void	container_init(t_container *container)
{
	container->end = 0;
	container->start = 0;
	container->size = 0;
}

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
		ft_zeromem((*end)->data, sizeof(unsigned int) * ARRAY_LEN);
	}
	return (*end);
}

void	container_add(t_container *container, int x)
{
	unsigned int val = x && 1;
	int bit_pos;		// bit pos in array
	int pos;			// pos in array
	int arr_bit_pos;	// bit pos in int

	// print_bit_array(container);

	if (container->size % (ARRAY_LEN * sizeof(unsigned int) * BITS_IN_BYTE) == 0)
	{
		list_arr_add(&(container->start), &(container->end));
	}
	container->size++;

	bit_pos = (container->size - 1) % (ARRAY_LEN * sizeof(unsigned int) * BITS_IN_BYTE);
	pos = bit_pos / (sizeof(unsigned int) * BITS_IN_BYTE);
	arr_bit_pos = bit_pos % (sizeof(unsigned int) * BITS_IN_BYTE);
	container->end->data[pos] = container->end->data[pos] | (val << arr_bit_pos);
}

int		is_in_squre(t_square *square, int line, int col)
{
	if ((square->x >= col) && (square->x - square->size < col)
				&& (square->y >= line) && (square->y - square->size < line))
		return 1;
	return 0;
}