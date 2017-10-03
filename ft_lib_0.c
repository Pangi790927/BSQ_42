#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

/// needs implementation
int		ft_atoi(char *str)
{
	return atoi(str);
}

/// needs implementation
void	ft_putstr(char *str)
{
	printf("%s", str);
}

int ft_min(int a, int b)
{
	return (a < b ? a : b);
}

void	ft_zeromem(void *mem, int size)
{
	int i = 0;
	while (i < size)
		((char*)mem)[i++] = 0;
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}