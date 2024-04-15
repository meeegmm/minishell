#include "../inc/parsing.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]); //нужно ли устанавливать в NULL?
		i++;
	}
	free(tab);
}


//is it possible to combine these 3 functions ?

void free_group_list(t_group *group)
{
	t_group *tmp;
	while(group != NULL)
	{
		tmp = group->next;
		if(group->cmd)
			free_tab(group->cmd);
		if(group->app_out)
			free(group->app_out);
		if(group->redir_in)
			free(group->redir_in);
		if(group->redir_out)
			free(group->redir_out);
		if(group->app_in)
			free(group->app_in);
		free(group);
		group = tmp;
	}
}

void free_tokens(t_tokens *list)
{
	t_tokens *tmp;
	while(list != NULL)
	{
		tmp = list->next;
		if(list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}

void free_envp_list(t_list_env *list)
{
	t_list_env *tmp;
	while(list != NULL)
	{
		tmp = list->next;
		if(list->key)
			free(list->key);
		if(list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}