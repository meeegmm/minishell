/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_m_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madmeg <madmeg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:55:42 by memarign          #+#    #+#             */
/*   Updated: 2024/05/22 20:36:06 by madmeg           ###   ########.fr       */
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
			//print error msg
			break ;
		}
		else if (group->flag_fail == 0)
		{
			if (group->next != NULL)
				ft_pipe(exec);
			simple_cmd(exec, group, env);
		}
		// printf("exec stat = %d\n", exec->stat);
		// builtin_error(exec, group);
		// status = group->flag_fail;
		group = group->next;
	}
}

void	reset_minish(t_exec *exec)
{
	close_fds(exec);
	init_exec(exec);
	// set_io(exec);
}
