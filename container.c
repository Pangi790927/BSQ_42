#include "container.h"

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"

#include <stdio.h>

/// functie ajutataoare ce printeaza continutul lui container
void	print_bit_array(t_container *container)
{
	t_list_arrays *current_node = container->start;

	int total_it = 0;
	int node_count = 0;
	while (current_node && total_it < container->size)
	{
		int it = 0;
		node_count++;
		printf("node: %d\n", node_count);
		while ((it < ARRAY_LEN) && total_it < container->size)
		{
			unsigned int bit = 1;
			while (bit && total_it < container->size)
			{
				printf("%d", (bit & current_node->data[it]) && 1);
				bit = (bit << 1);
				total_it++;
			}
			printf("	total_it: %d 	data: %d \n", total_it, current_node->data[it]);
			it++;
		}
		printf(" -- \n");
		current_node = current_node->next;
	}
}

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

void	print_solution(int line_len, t_container *container, t_square *sol, char *str)
{
	// print_bit_array(container);

	int i;
	int bit_pos;		// bit pos in array
	int pos;			// pos in array
	int arr_bit_pos;	// bit pos in int
	int line;
	int col;
	char *array;

	array = (char *)malloc(sizeof(char) * line_len);

	t_list_arrays *currentNode;

	i = 0;
	currentNode = container->start;
	while (i < container->size && currentNode)
	{

		if (((i + 1) % (ARRAY_LEN * sizeof(unsigned int) * BITS_IN_BYTE) == 0))
			currentNode = currentNode->next;	

		bit_pos = (i) % (ARRAY_LEN * sizeof(unsigned int) * BITS_IN_BYTE);
		pos = bit_pos / (sizeof(unsigned int) * BITS_IN_BYTE);
		arr_bit_pos = bit_pos % (sizeof(unsigned int) * BITS_IN_BYTE);

		int val = (currentNode->data[pos] & (1 << arr_bit_pos)) && 1; 
		
		line = i / line_len;
		col = i % line_len;

		if (is_in_squre(sol, line, col))
			array[col] = str[2];
		else 
		if (val)
			array[col] = str[1];
		else
			array[col] = str[0];

		if (((i + 1) % line_len == 0))
		{
			col = write(1, array, line_len);
			ft_putchar('\n');
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
		free(to_delete->data);
		free(to_delete);
		current_node = current_node->next;
	}
}