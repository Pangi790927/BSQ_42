#include <stdio.h>

#include "solver.h"

int main(int argc, char const *argv[])
{
	int fd;

	fd = open("exemplu.ex", O_RDONLY);
	solver_solve();
	close(fd);
	
	return 0;
}