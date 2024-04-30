/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_fd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:18:58 by memarign          #+#    #+#             */
/*   Updated: 2024/04/30 11:19:03 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	set_io(t_exec *exec)
{
	dup2(exec->fd_in, 0);
	dup2(exec->fd_out, 1);
}

void	init_exec(t_exec *exec)
{
	exec->status = -1;
	exec->fd_in = -1;
	exec->fd_out = -1;
	exec->pfd_in = -1;
	exec->pfd_out = -1;
	exec->pid = -1;
}

void	close_fds(t_exec *exec)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	if (exec->fd_out > 0)
		close(exec->fd_out);
	if (exec->pfd_in > 0)
		close(exec->pfd_in);
	if (exec->pfd_out > 0)
		close(exec->pfd_out);
}
