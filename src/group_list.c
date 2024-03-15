#include "../inc/parsing.h"

t_group *invalid_group(int flag)
{
	t_group *group;
	group = malloc(sizeof(t_group));
	if(!group || group == NULL)
	{
		perror("group malloc");
		return (NULL);
	}
	group->cmd = NULL;
	group->next = NULL;
    group->source = NULL;
    group->destination = NULL;
	group->next = NULL;
	group->flag_fail = flag;
	return (group);
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

t_group *get_group(t_tokens *list, char **envp)
{
	t_group *group;

	group = malloc(sizeof(t_group));
	if(!group)
	{
		perror("group malloc");
		return (NULL); 				//malloc pb
	}
	group->cmd = get_tab(list);
	if(!group->cmd)
	{
		perror("malloc problem");
		return (NULL);
	}
	if(is_built(group->cmd[0]) == 0)
	{
		group->cmd[0] = cmd_check(group->cmd, envp);
		if(group->cmd[0] == NULL)
		{
			free(group);
			return (invalid_group(127)); //cmd not found
		}
	}
	group->flag_fail = 0;
	group->next = NULL;
	return (group);
}

//get_group_list
// t_group *get_group_list(t_tokens *list, char **envp)
// {
// 	int i;
// 	t_group *begin;
// 	t_group *curr;

// 	begin = get_group(list, envp);
// 	curr = begin;
// 	i = 1;
// 	while( i <= get_group_nb(list))
// 	{
// 		while(list)
// 		list = list->next;
// 		curr->next = get_group(list, envp);
// 		curr = curr->next;
// 		i++;
// 	}
// 	return (begin);
// }