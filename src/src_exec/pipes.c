#include "../../inc/exec.h"
// #include "../../inc/parsing.h"

//doesn't close well when pipe
void		ft_pipe(t_exec *exec)
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
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec->pfd_in = pipe_fd[0];
		exec->pid = -1;
		return ;
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec->pfd_out = pipe_fd[1];
		exec->pid = pid;
		return ;
	}
}