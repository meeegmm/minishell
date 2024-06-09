/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madmeg <madmeg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:56 by memarign          #+#    #+#             */
/*   Updated: 2024/06/09 12:14:50 by madmeg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	redir_in(t_exec *exec, t_group *group)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	exec->fd_in = open(group->redir_in, O_RDONLY | S_IRWXU);
	dup2(exec->fd_in, 0);
	close(exec->fd_in);
}

void	redir_out(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->redir_out, \
						O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	dup2(exec->fd_out, 1);
	close(exec->fd_out);
}

void	append_out(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->app_out, O_APPEND | S_IRWXU);
	dup2(exec->fd_out, 1);
	close(exec->fd_out);
}

void	ft_redir(t_exec *exec, t_group *group)
{
	if (group->redir_in != NULL)
		redir_in(exec, group);
	else if (group->redir_out != NULL)
		redir_out(exec, group);
	else if (group->app_out != NULL)
		append_out(exec, group);
}
