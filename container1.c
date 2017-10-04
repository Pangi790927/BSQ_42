#include "container.h"

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"

int		container_get_val(t_list_arrays *node, int i)
{
	int bit_pos;		// bit pos in array
	int pos;			// pos in array
	int arr_bit_pos;	// bit pos in int

	bit_pos = (i) % (ARRAY_LEN * sizeof(unsigned int) * BITS_IN_BYTE);
	pos = bit_pos / (sizeof(unsigned int) * BITS_IN_BYTE);
	arr_bit_pos = bit_pos % (sizeof(unsigned int) * BITS_IN_BYTE);

	return ((node->data[pos] & (1 << arr_bit_pos)) && 1); 
}

int		print_solution_char(int val, int line, int col, t_square *sol)
{
	if (is_in_squre(sol, line, col))
		return 2;
	else if (val)
		return 1;
	else
		return 0;
}

void	print_solution(int line_len, t_container *container, t_square *sol, char *str)
{
	int i;
	int line;
	int col;
	char *array;
	t_list_arrays *current_node;

	array = (char *)malloc(sizeof(char) * (line_len + 1));

	i = 0;
	current_node = container->start;
	while (i < container->size && current_node)
	{
		if (((i) % (ARRAY_LEN * sizeof(unsigned int) * BITS_IN_BYTE) == 0) && i != 0)
			current_node = current_node->next;	

		line = i / line_len;
		col = i % line_len;

		array[col] = str[print_solution_char(container_get_val(current_node, i)
			, line, col, sol)];

		if (((i + 1) % line_len == 0))
		{
			array[line_len] = '\n';
			col = write(1, array, line_len + 1);
		}
		i++;
	}
	free(array);
}

void	container_free_mem(t_container *container)
{
	t_list_arrays *current_node;
	t_list_arrays *to_delete;

	current_node = container->start;
	while (current_node)
	{
		to_delete = current_node;
		current_node = current_node->next;
		free(to_delete->data);
		free(to_delete);
	}
}