/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:01:44 by memarign          #+#    #+#             */
/*   Updated: 2024/04/30 13:06:30 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	ft_child(t_exec *exec, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	exec->pfd_in = pipe_fd[0];
	exec->pid = -1;
}

void	ft_parent(t_exec *exec, int *pipe_fd, int pid)
{
	waitpid(-1, NULL, 0);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	exec->pfd_out = pipe_fd[1];
	exec->pid = pid;
}
//doesn't close well when pipe

void	ft_pipe(t_exec *exec)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("Error ft_pipe");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ft_child(exec, pipe_fd);
		return ;
	}
	else
	{
		ft_parent(exec, pipe_fd, pid);
		return ;
	}
}
