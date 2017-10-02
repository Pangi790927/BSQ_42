////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"
#include "solver.h"

// to be removed
#include <stdio.h>

int		solver_map_error(t_map *map)
{
	if (map->error == ERROR)
		return 1;
	else
		return 0;
}

int		solver_set_error(t_map *map)
{
	if (map->error == NO_ERROR)
	{
		ft_putstr("map error\n");
		map->error = ERROR;
	}
	return 0;
}

void	solver_square_init(t_square *square)
{
	square->x = -1;
	square->y = -1;
	square->size = 0;
}

void	sovler_map_init(t_map *map)
{
	map->error = NO_ERROR;
	
	map->fill = 0;
	map->full = 0;
	map->empty = 0;

	map->line_count = 0;
	map->line_lenght = 0;

	solver_square_init(&(map->square));
}

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

	first_line = (char*)malloc(sizeof(char) * elem_count);
	
	if (!first_line || elem_count == 0)
		return (char *)(0) + (solver_set_error(map));

	while (list)
	{
		first_line[elem_count - 1] = list->data;
		list = list_remove(list);
	}

	return first_line;
}

int solver_read_line(char *line, int fd, t_map *map)
{
	/// we also need to memoryze the line after reading it 
	char c;
	if (read(fd, line, map->line_lenght) != map->line_lenght)
		return (solver_set_error(map));
		
	/// we read the \n character and we expect that the character is there
	return (read(fd, &c, 1));
}

void	solver_set_square(int x, int y, int size, t_square *square)
{
	square->x = x;
	square->y = y;
	square->size = size;
}

int solver_dynamic_rule(char *line, int *results, int col, t_map *map)
{
	int result;

	printf("%c", line[col]);
	container_add(&(map->container), line[col] == map->full);

	result = 0;
	if (!(line[col] == map->empty || line[col] == map->full))
	{
		solver_set_error(map);
		return (-1);
	}

	if (col == 0)
	{
		results[map->line_lenght] = results[col];
		return (line[col] == map->empty);
	}

	if (line[col] == map->empty)
	{
		result = 1 + ft_min(results[map->line_lenght],
				ft_min(results[col], results[col - 1]));
		results[map->line_lenght] = results[col];
	}

	return result;
}

t_map	*solver_dynamic(int fd, t_map *map)
{
	char *line;
	int *result_vec;
	int line_index;
	int col_index;

	line = solver_get_first_line(fd, map);

	result_vec = (int*)malloc((map->line_lenght + 1)* sizeof(int));

	/// we zero the memory so we can use it on the first line
	ft_zeromem((void *)result_vec, (map->line_lenght + 1)* sizeof(int));

	line_index = 0;
	while (line_index < map->line_count - 1)
	{
		col_index = 0;
		if (!solver_read_line(line, fd, map))
			return map;
	
		while (col_index < map->line_lenght)
		{
			/// if we encountered an error we return
			if ((result_vec[col_index] =
					solver_dynamic_rule(line, result_vec, col_index, map)) == -1)
				return map;

			/// if we found a bigger square set it
			if (map->square.size < result_vec[col_index])
				solver_set_square(col_index, line_index,
						result_vec[col_index], &(map->square));
			
			col_index++;
		}
		printf("\n");
		line_index++;
	}
	return map;
}

t_map	*solver_solve(int fd, t_map *map)
{
	/// init the values of the map
	sovler_map_init(map);	

	/// read the legend
	solver_parse_legend(fd, map);	

	/// check if the legend is ok
	if (solver_map_error(map))
		return map;

	/// solve the acutal problem 
	solver_dynamic(fd, map);

	/// check if map is still ok
	if (solver_map_error(map))
		return map;

	return map;
	/// printing will be managed from the outside
}