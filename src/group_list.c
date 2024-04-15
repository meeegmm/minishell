#include "../inc/parsing.h"
#include "../inc/minishell.h"

void invalid_group(t_group *group, int flag)
{
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->app_in = NULL;
	group->next = NULL;
}

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

t_tokens *move_after_pipe(t_tokens *list)
{
	while(list->type != 5 && list->next != NULL)
		list = list->next;
	return (list->next);
}

t_group *get_group(t_tokens *list, t_list_env *env)
{
	t_tokens *start;
	t_group *group; //static + проверка на NULL
	char **new_envp;

	start = list;
	group = malloc(sizeof(t_group));
	if(!group || group == NULL) //to remove "group == NULL" ?
		return (NULL);
    invalid_group(group, 0);
	group->cmd = get_cmd_tab(list);
	if (!group->cmd)
	{
		free_tokens(list);
		invalid_group(group, 1);
	}
	if(is_built(group->cmd[0]) == 0)
	{
		new_envp = get_envp(env);
		group->cmd[0] = cmd_check(group->cmd, new_envp);
		if(group->cmd[0] == NULL)
		{
			free(group->cmd);
			invalid_group(group, 127); //cmd not found
			free_tokens(list);
			ft_putstr_err("Command not found\n");
		}
		free(new_envp);
	}
	list = start;
	if (get_files(list, group) != 0)
	{
		// free(group->cmd);
		// free(group->cmd[0]);
		invalid_group(group, 1);
		// free_tokens(list);
	}
	return (group);
}

t_group *get_group_list(t_tokens *list, t_list_env *env)
{
	t_group *begin_gr;
	t_group *curr_gr;

	begin_gr = get_group(list, env);
	if(!begin_gr)
	{
		free_tokens(list);
		return (NULL);
	}
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
			begin_gr->next = get_group(list, env);
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