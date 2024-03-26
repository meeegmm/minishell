#include "../inc/parsing.h"
#include "../inc/minishell.h"

int get_group_nb(t_tokens *list)
{
    int group_nb;

    group_nb = 1;
    while(list != NULL)
    {
        if(list->type == 5)
            group_nb++;
        list = list->next;
    }
    return (group_nb);
}

char **get_cmd_tab(t_tokens *list)
{
	int len;
	int i;
	t_tokens *start;
    char **cmd_tab;

	len = 0;
	i = 0;
	while(list != NULL && list->next != 0 && list->type != 0 && list->next->type == 0)
		list = list->next->next;
	start = list;
	while (list != NULL && list->type == 0) //найти кол-во элементов таблицы cmd
	{
		len++;
		list = list->next;
	}
	cmd_tab = malloc(sizeof(char *) * (len + 1));
	if(!cmd_tab)
		return (NULL);
	list = start;
	while(i < len && list != NULL)
	{
		cmd_tab[i] = ft_strdup(list->value);
		i++;
		list = list->next;
	}
	cmd_tab[i] = NULL;

    // printf("Here is the group->cmd : ");
    // print_tab(cmd_tab);
	// printf("\n\n");
	return (cmd_tab);
}


t_group *get_files(t_tokens *list, t_group *group)
{
	while(list->type != 5 && list->next != NULL)
	{
		if (list->type == 1  && list->next->type == 0)
			{
				group->redir_in = infile_access(list, group->redir_in);
				if(group->redir_in == NULL)
				{
					free_group_list(group);
					group = invalid_group(1);
				}
			}
			else if (list->type == 2  && list->next->type == 0)
			{
				group->redir_out = outfile_access(list, group->redir_out);
				if(group->redir_out == NULL)
				{
					free_group_list(group);
					group = invalid_group(1);
				}
			}
			else if (list->type == 4  && list->next->type == 0)
			{
				group->app_out = outfile_access(list, group->app_out);
				if(group->app_out == NULL)
				{
					free_group_list(group);
					group = invalid_group(1);
				}
			}
			list = list->next;
	}
	return (group);
}

t_tokens *move_after_pipe(t_tokens *list)
{
	while(list->type != 5 && list->next != NULL)
		list = list->next;
	return (list->next);
}

t_group *get_group(t_tokens *list, char **envp)
{
	t_tokens *start;
	t_group *group;

	start = list;
	// printf("debut de get_group\n");
    group = invalid_group(0); ///!!!!!
	if(group == NULL)
		return (NULL);
	group->cmd = get_cmd_tab(list);

	if(!group->cmd)
	{
		free(group);
		free_tokens(list); //???
		return (invalid_group(1)); //malloc pb
	}
	if(is_built(group->cmd[0]) == 0)
	{
		//convertir liste envp en char **new_envp
		group->cmd[0] = cmd_check(group->cmd, envp);
		// printf("%s", group->cmd[0]);
		if(group->cmd[0] == NULL)
		{
			free(group->cmd);
			free(group);
			group = invalid_group(127); //cmd not found
			free_tokens(list);
			ft_putstr_err("Command not found\n");
			// return (invalid_group(127)); //cmd not found
		}
	}
	list = start;
	group = get_files(list, group);
	return (group);
}

t_group *get_group_list(t_tokens *list, char **envp)
{
	t_group *begin_gr;
	t_group *curr_gr;

	begin_gr = get_group(list, envp);
	if(!begin_gr)
	{
		free_tokens(list);
		return (NULL);
	}

    printf("Print first group : \n");
    print_group(begin_gr);
    printf("\n");
	printf("HERE! %s\n", list->value);

    if(get_group_nb(list) == 1)
	{
		free_tokens(list);
		return (begin_gr);
	}
    else
	{
		curr_gr = begin_gr;
        while(get_group_nb(list))
        {
            list = move_after_pipe(list); //мб избыточно, учитывая условие while

            if(list == NULL) //должно входить в проверку синтаксиса раньше
                break;		
			begin_gr->next = get_group(list, envp);
			if(!begin_gr->next)
			{
				free_group_list(curr_gr);
				break;
			}
			begin_gr = begin_gr->next;
		}
		free_tokens(list);
    }
	return (curr_gr); //change to begin_gr
}