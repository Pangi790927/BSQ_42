////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include "ft_lib.h"

enum {NO_ERROR, ERROR};

typedef struct	s_map
{
	int line_count;
	int line_lenght;
	int error;

	char empty;
	char full;
	char fill;
}				t_map;

int		solver_map_error(t_map *map)
{
	if (map->error == ERROR)
		return 1;
	else
		return 0;
}

void	solver_set_error(t_map *map)
{
	if (map->error == NO_ERROR)
	{
		ft_putstr("map error\n");
		map->error = ERROR;
	}
}

void	sovler_map_init(t_map *map)
{
	map->error = NO_ERROR;
	
	map->fill = 0;
	map->full = 0;
	map->empty = 0;

	map->line_count = 0;
	map->line_lenght = 0;
}

void	solver_parse_legend(int fd, t_map *map)
{
	char str[21];
	int line_len;

	lline_len = 0;
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
			set_error(&map);
	}
	else
		set_error(&map);
}

void	solver_get_first_line(int fd, t_map *map)
{
	
}

t_map	*solver_solve(int fd)
{
	t_map map;

	sovler_map_init(&map);
	solver_parse_legend(fd, &map);	
	
	if (solver_map_error(&map))
		return &map;

	solver_get_first_line(fd, &map);
}