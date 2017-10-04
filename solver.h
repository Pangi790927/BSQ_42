#ifndef SOLVER_H
# define SOLVER_H

#include "square.h"
#include "container.h"

enum {NO_ERROR, ERROR};

typedef struct	s_map
{
	int		line_count;
	int		line_lenght;
	int		error;

	char	empty;
	char	full;
	char	fill;

	char	*line_buffer;
	int		*result_buffer;

	t_square square;
	t_container container;
}				t_map;

t_map	*solver_solve(int fd, t_map *map);
int		solver_map_error(t_map *map);
void	solver_parse_legend(int fd, t_map *map);
char	*solver_get_first_line(int fd, t_map *map);
int 	solver_read_line(char *line, int fd, t_map *map);
void	solver_set_square(int x, int y, int size, t_square *square);
void	solver_dynamic_init_line_and_alloc(t_map *map, int fd);
void	solver_dynamic_update_solution(t_map *map, int line, int col);
int 	solver_dynamic_rule(char *line, int *results, int col, t_map *map);
t_map	*solver_dynamic(int fd, t_map *map);
int		solver_set_error(t_map *map);
void	solver_square_init(t_square *square);
void	sovler_map_init(t_map *map);

#endif