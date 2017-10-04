////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <unistd.h>
#include "ft_lib.h"
#include "solver.h"

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
