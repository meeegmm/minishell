/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:41 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 18:10:30 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	redir_in2(t_exec *exec, t_group *group)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	exec->fd_in = open(group->redir_in, O_RDONLY | S_IRWXU);
	dup2(exec->fd_in, 0);
	// if (exec->fd_in > 0)
	close(exec->fd_in);
}

void	redir_out2(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->redir_out, \
						O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	close(exec->fd_out);
	dup2(exec->fd_out, 1);
}

void	append_out2(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->app_out, O_APPEND | S_IRWXU);
	close(exec->fd_out);
	dup2(exec->fd_out, 1);
}

void	ft_redir2(t_exec *exec, t_group *group)
{
	if (group->redir_in != NULL)
		redir_in2(exec, group);
	else if (group->redir_out != NULL)
		redir_out2(exec, group);
	else if (group->app_out != NULL)
		append_out2(exec, group);
}