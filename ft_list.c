#include <stdlib.h>
#include "ft_list.h"

t_list_char	*list_add(t_list_char *node, char elem)
{
	t_list_char *newElem = (t_list_char*)malloc(sizeof(t_list_char));

	if (!newElem)
		return 0;

	newElem->next = node;
	newElem->data = elem;

	return (newElem);
}

t_list_char	*list_remove(t_list_char *node)
{
	if (!node)
		return 0;

	t_list_char *next = node->next;
	free(node);

	return (next);
}