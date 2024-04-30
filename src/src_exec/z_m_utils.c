/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_m_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:27:05 by memarign          #+#    #+#             */
/*   Updated: 2024/04/30 13:23:18 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	minish(t_exec *exec, t_group *group, t_list_env *env)
{
	while (group != NULL)
	{
		if (group->flag_fail == 2 || (group->flag_fail == 127 \
									&& group->next == NULL))
		{
			reset_minish(exec, group);
			break ;
		}
		else if (group->flag_fail == 0)
		{
			if (group->next != NULL)
				ft_pipe(exec);
			simple_cmd(exec, group, env);
		}
		if (exec->status == 0)
			group = group->next;
		else
			//print error
			return ;
	}
}

void	reset_minish(t_exec *exec, t_group *start)
{
	if (start != NULL)
		free_group_list(start);
	close_fds(exec);
	init_exec(exec);
	set_io(exec);
}
