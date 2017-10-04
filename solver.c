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
	size_t ret_val;
	if (map->error == NO_ERROR)
	{
		ret_val = write(2, "map error\n", 10);
		ret_val = ret_val * 2;
		// ft_putstr("map error\n");
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

	map->line_buffer = 0;
	map->result_buffer = 0;

	solver_square_init(&(map->square));
	container_init(&(map->container));
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

int solver_dynamic_rule(char *line, int *results, int col, t_map *map)
{
	int result;

	// printf("%d ", line[col]);
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
		result = 1 + MIN(results[map->line_lenght],
				MIN(results[col], results[col - 1]));
		results[map->line_lenght] = results[col];
	}

	return result;
}

void	solver_dynamic_init_line_and_alloc(t_map *map, int fd)
{
	map->line_buffer = solver_get_first_line(fd, map);
	map->result_buffer = (int*)malloc((map->line_lenght + 1)* sizeof(int)); 
	ft_zeromem((void *)(map->result_buffer), (map->line_lenght + 1)
		* sizeof(int));
}

void	solver_dynamic_update_solution(t_map *map, int line, int col)
{
	if (map->square.size < map->result_buffer[col])
		solver_set_square(col, line,
				map->result_buffer[col], &(map->square));
}

t_map	*solver_dynamic(int fd, t_map *map)
{
	int line_it;
	int col_it;

	solver_dynamic_init_line_and_alloc(map, fd);
	if(solver_map_error(map))
		return map;
	line_it = 0;
	while (line_it < map->line_count)
	{
		col_it = 0;
		if ((line_it != 0) && (!solver_read_line(map->line_buffer, fd, map)))
			return map;
		while (col_it < map->line_lenght)
		{
			if ((map->result_buffer[col_it] =
					solver_dynamic_rule(map->line_buffer, map->result_buffer,
					col_it, map)) == -1)
				return map;
			solver_dynamic_update_solution(map, line_it, col_it);
			col_it++;
		}
		line_it++;
	}
	return map;
}

t_map	*solver_solve(int fd, t_map *map)
{
	char useless;
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

	/// comment bellow is not used because it breaks the input
	/// from standard in
	if (read(fd, &useless, 1) != 0)
		solver_set_error(map);

	return map;
	/// printing will be managed from the outside
}