/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_m_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:55:42 by memarign          #+#    #+#             */
/*   Updated: 2024/05/17 12:49:58 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	minish(t_exec *exec, t_group *group, t_list_env *env)
{
	while (group != NULL)
	{
		if (group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL))
		{
			reset_minish(exec);
			return ;
		}
		else if (group->flag_fail == 0)
		{
			if (group->next != NULL)
				ft_pipe(exec);
			simple_cmd(exec, group, env);
		}
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
