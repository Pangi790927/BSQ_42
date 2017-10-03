#ifndef FT_LIB_H
# define FT_LIB_H

# include "ft_list.h"

# define MIN(a, b) (a < b ? a : b)

// int 	ft_min(int a, int b);
int		ft_atoi(char *str);
void	ft_putstr(char *str);
int		ft_putchar(char c);
void	ft_zeromem(void *mem, int size);

#endif