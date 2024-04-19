#include "../../inc/exec.h"

void	init_std(t_exec *exec)
{
	exec->infile = dup(STDIN_FILENO);
	exec->outfile = dup(STDOUT_FILENO);
}

void	reset_std(t_exec *exec)
{
	dup2(exec->infile, STDIN_FILENO);
	dup2(exec->outfile, STDOUT_FILENO);
}

void	close_std(t_exec *exec)
{
	close(exec->infile);
	exec->infile = -1;
	close(exec->outfile);
	exec->outfile = -1;
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
