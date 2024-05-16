/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_m_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:55:42 by memarign          #+#    #+#             */
/*   Updated: 2024/05/11 04:04:35 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	minish(t_exec *exec, t_group *group, t_list_env *env)
{
	while (group != NULL)
	{
		if (group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL))
		{
			status = group->flag_fail;
			reset_minish(exec);
			return ;
		}
		else if (group->flag_fail == 0)
		{
			status = group->flag_fail;
			if (group->next != NULL)
				ft_pipe(exec);
			simple_cmd(exec, group, env);
		}
		else
			status = group->flag_fail;
		// if (exec->stat == 0)
		group = group->next;
		// else
		// 	return ;
	}
}

void	reset_minish(t_exec *exec)
{
	close_fds(exec);
	init_exec(exec);
	set_io(exec);
}
