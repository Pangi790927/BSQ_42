////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"
#include "solver.h"

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