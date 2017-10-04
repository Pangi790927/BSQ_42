////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"
#include "solver.h"

// to be removed
#include <stdio.h>

void	solver_parse_legend(int fd, t_map *map)
{
	char str[21];
	int line_len;

	line_len = 0;
	while (read(fd, str + line_len, 1) && str[line_len] != '\n'
			&& line_len < 20)
		line_len++;

	if (line_len >=4 && line_len <= 18)
	{
		map->fill = str[line_len - 1];
		map->full = str[line_len - 2];
		map->empty = str[line_len - 3];

		str[line_len - 3] = 0;

		map->line_count = ft_atoi(str);

		if (map->line_count <= 0)
			solver_set_error(map);
	}
	else
		solver_set_error(map);
}

char	*solver_get_first_line(int fd, t_map *map)
{
	/// we also need to memoryze the line after reading it 

	t_list_char *list;
	int elem_count;
	char elem;
	char *first_line;

	list = 0;
	elem = 0;
	elem_count = 0;
	while (read(fd, &elem, 1) && elem != '\n')
	{
		list = list_add(list, elem);
		elem_count++;
	}
	map->line_lenght = elem_count;

	first_line = (char*)malloc(sizeof(char) * (elem_count + 1));
	
	if (!first_line || elem_count == 0 || elem != '\n')
		return (char *)(0) + (solver_set_error(map));

	while (list)
	{
		first_line[--elem_count] = list->data;
		list = list_remove(list);
	}

	if (elem != '\n')
		return (char *)(0) + (solver_set_error(map));

	return first_line;
}

int solver_read_line(char *line, int fd, t_map *map)
{
	/// we also need to memoryze the line after reading it 
	if (read(fd, line, map->line_lenght + 1) != map->line_lenght + 1)
		return (solver_set_error(map));
		
	/// we read the \n character and we expect that the character is there
	if (line[map->line_lenght] != '\n')
		return (solver_set_error(map));

	return (1);
}

void	solver_set_square(int x, int y, int size, t_square *square)
{
	square->x = x;
	square->y = y;
	square->size = size;
}
