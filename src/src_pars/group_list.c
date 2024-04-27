/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:25 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/27 02:17:31 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include "../../inc/minishell.h"

int	get_group_nb(t_tokens *list)
{
	int	group_nb;

	group_nb = 1;
	while (list != NULL)
	{
		if (list->type == 5)
			group_nb++;
		list = list->next;
	}
	return (group_nb);
}

t_tokens	*move_after_pipe(t_tokens *list)
{
	while (list->type != 5 && list->next != NULL)
		list = list->next;
	return (list->next);
}

t_group	*get_group(t_tokens *list, t_list_env *env)
{
	char		**new_envp;
	t_tokens	*start;
	t_group		*group;

	start = list;
	group = create_init_group();
	group->cmd = get_cmd_tab(list);
	if (!group->cmd)
		invalid_group(group, 1);
	if (is_built(group->cmd[0]) == 0)
	{
		new_envp = get_envp(env);
		group->cmd[0] = cmd_check(group->cmd, new_envp);
		if (group->cmd[0] == NULL)
		{
			free(group->cmd);
			invalid_group(group, 127);
			ft_putstr_err("Command not found\n");
		}
		free_tab(new_envp);
	}
	list = start;
	if (get_files(list, group) != 0)
		invalid_group(group, 1);
	return (group);
}

int	get_new_node(t_tokens **list, t_list_env *env,
	t_group **begin_gr, t_group *curr_gr)
{
	*list = move_after_pipe(*list);
	if (*list == NULL)
		return (1);
	(*begin_gr)->next = get_group(*list, env);
	if (!(*begin_gr)->next)
	{
		free_group_list(curr_gr);
		return (1);
	}
	(*begin_gr) = (*begin_gr)->next;
	return (0);
}

t_group	*get_group_list(t_tokens *list, t_list_env *env)
{
	t_group	*begin_gr;
	t_group	*curr_gr;

	begin_gr = get_group(list, env);
	if (!begin_gr)
		return (NULL);
	if (get_group_nb(list) == 1)
		return (begin_gr);
	else
	{
		curr_gr = begin_gr;
		while (get_group_nb(list))
		{
			if (get_new_node(&list, env, &begin_gr, curr_gr))
				break ;
		}
	}
	return (curr_gr);
}
