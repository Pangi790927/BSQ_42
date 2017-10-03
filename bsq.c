#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "solver.h"

// to be removed
#include <stdio.h>

void	solve(char *str, int is_stdin)
{
	int fd;
	t_map map;

	if (is_stdin)
		fd = 0;
	else
		fd = open(str, O_RDONLY);
	
	solver_solve(fd, &map);

	char chars[3];
	chars[0] = map.empty;
	chars[1] = map.full;
	chars[2] = map.fill;
	
	if (!solver_map_error(&map))
		print_solution(map.line_lenght, &(map.container), &(map.square), chars);
	
	/// free the memory even if memory occured
	if (map.line_buffer)
		free(map.line_buffer);
	
	if (map.result_buffer)
		free(map.result_buffer);
	
	container_free_mem(&(map.container));

	close(fd);
}

int main(int argc, char **argv)
{
	int i = 0;

	if (argc <= 1)
	{
		solve("", 1);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		solve(argv[i], 0);
		i++;
	}
	return 0;
}