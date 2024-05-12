/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:25 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/12 21:38:17 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

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
	t_tokens	*start;
	t_group		*group;
	int			flag;

	start = list;
	group = create_init_group();
	group->cmd = get_cmd_tab(list);
	if (!group->cmd)
	{
		list = start;
		if(get_files(list, group) != 0)
			invalid_group(group, 1);
		return (group);
	}
	flag = cmd_check(&(group->cmd[0]), env);
	if (flag > 0)
	{
		free_tab(group->cmd);
		invalid_group(group, flag);
	}
	else
	{
		if (group->cmd && group->cmd[0] != NULL && group->cmd[0][0] != '\0'
			&& get_files(start, group) != 0)
		{
			free_tab(group->cmd);
			invalid_group(group, 1);
		}
	}
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
