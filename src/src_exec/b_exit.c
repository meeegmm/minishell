/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:28:22 by memarign          #+#    #+#             */
/*   Updated: 2024/04/30 12:28:23 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//go to parent or end shell

void	end_minish(t_exec *exec, t_group *start, t_list_env *env)
{
	if (start != NULL)
		free_group_list(start);
	if (env != NULL)
		free_envp_list(env);
	close_fds(exec);
	init_exec(exec);
	rl_clear_history();
	if (exec->status == 0)
		exit(EXIT_SUCCESS); //use tty?
	else
		exit(EXIT_FAILURE);
}
//use signals
void	builtin_exit(t_exec *exec, t_group *group, t_list_env *env)
{
	if (exec->status == 2)
	{
		ft_putstr_fd("minishell", group->cmd[0], 2);
		//too many arguments
	}
	else if (exec->status == 3)
	{
		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
		//wrong path
	}
	else if (exec->status == 4)
	{
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
		// exit(EXIT_FAILURE);
	}
	else if (exec->status == 5)
	{
		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
		// //invalid option
	}
	end_minish(exec, group, env);
}
