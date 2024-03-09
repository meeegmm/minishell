#include "../../inc/parsing.h"

int	get_tokens_nb(t_tokens *list)
{
	int	node_nb;

	node_nb = 0;
	while (list != NULL)
	{
		list = list->next;
		node_nb++;
	}
	return (node_nb);
}

char	**get_tab(t_tokens *list) //разбить на функции поменьше
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (get_tokens_nb(list) + 1));
	if (!tab)
		return (NULL);
	while (list != NULL)
	{
		tab[i] = ft_strdup(list->value);
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

