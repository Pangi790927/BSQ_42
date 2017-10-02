#ifndef FT_LIST_H
# define FT_LIST_H value

typedef struct		s_list_char
{
	char data;
	struct s_list_char *next;
}					t_list_char;

t_list_char	*list_add(t_list_char *node, char elem);
t_list_char	*list_remove(t_list_char *node);

#endif