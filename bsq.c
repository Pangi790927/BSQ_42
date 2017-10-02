#include <unistd.h>
#include <fcntl.h>

#include "solver.h"

// to be removed
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i = 0;
	while (i < argc)
		printf("%s\n", argv[i++]);

	int fd;
	t_map map;

	fd = open("example.ex", O_RDONLY);
	solver_solve(fd, &map);

	printf("Map: line: %d, col: %d d\n", map.line_count, map.line_lenght);
	printf("empty: %c, full %c, fill, %c\n", map.empty, map.full, map.fill);
	printf("Solution: x: %d, y: %d, size: %d\n", map.square.x, map.square.y, map.square.size);
	close(fd);
	
	return 0;
}