#include "../../inc/parsing.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]); //is it correct? нужно ли устанавливать в NULL
		i++;
	}
	free(tab);
}

void free_group(t_group *lg)
{
	if(lg)
	{
		if(lg->cmd)
			free_tab(lg->cmd);
		// if(lg->source != NULL)
		// 	free(lg->source);
		// if(lg->destination != NULL)
			// free(lg->destination);
		free(lg); //нужно ли отдельно освобождать память пойнтера?
	}
}

void free_list(t_list_env *list) //rewrite the function => segfault pb
{
	t_list_env *tmp;
	while(list != NULL)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list->next);
		list = tmp;
	}
}

// void free_struct_exec(t_exec *p)
// {
// 	if(p->envp_list)
// 		free_list(p->envp_list);
// 	free(p);
// }