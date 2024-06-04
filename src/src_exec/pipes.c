/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:48 by memarign          #+#    #+#             */
/*   Updated: 2024/06/04 11:05:49 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//doesn't close well when pipe
void	child_pid(t_exec *exec, int *pipe_fd)
{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(pipe_fd[0], 0); //STDIN_FILENO
		exec->pfd_in = pipe_fd[0];
}
void	parent_pid(t_exec *exec, int *pipe_fd)
{
		waitpid(-1, NULL, 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(pipe_fd[1], 1); //STDOUT_FILENO
		exec->pfd_out = pipe_fd[1];
}
void		ft_pipe(t_exec *exec)
{
	pid_t	pid;
	int		pipe_fd[2];

	// pipe(pipe_fd);
	if (pipe(pipe_fd))
		return ; // -1?
	pid = fork();
	// printf("PIPE PID = %d\n\n", pid);
	if (pid == -1)
	{
		//return (1);
		perror("Error ft_pipe");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(pipe_fd[0], 0);
		exec->pfd_in = pipe_fd[0];
		// printf("PIPE EXEC PFD_IN = %d\n", exec->pfd_in);
		// printf("PIPE EXEC PFD_OUT = %d\n\n", exec->pfd_out);
		exec->pid = -1;
		// printf("AFTER PIPE EXEC_PID = %d\n\n", exec->pid);
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(pipe_fd[1], 1);
		exec->pfd_out = pipe_fd[1];
		exec->pid = pid;
		// printf("AFTER PIPE PARENT PID = %d\n", pid);
		// printf("AFTER PIPE PARENT EXEC_PID = %d\n\n", exec->pid);
		// printf("PIPE PARENT EXEC PFD_IN = %d\n", exec->pfd_in);
		// printf("PIPE PARENT EXEC PFD_OUT = %d\n\n", exec->pfd_out);
	}
}
