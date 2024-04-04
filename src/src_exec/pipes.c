#include "../../inc/exec.h"
#include "../../inc/parsing.h"

//* for pid?
void		ft_pipe(t_exec *exec)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		exec->pfd_in = pipe_fd[0];
		exec->pid = -1;
		return ;
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		exec->pfd_out = pipe_fd[1];
		exec->pid = pid;
		return ;
	}
}