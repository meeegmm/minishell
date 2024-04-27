#include "../../inc/exec.h"

// void	init_std(t_exec *exec)
// {
// 	exec->infile = dup(STDIN_FILENO);
// 	exec->outfile = dup(STDOUT_FILENO);
// }

void	set_io(t_exec *exec) //changed
{
	dup2(exec->fd_in, 0);
	dup2(exec->fd_out, 1);
}

// void	close_std(t_exec *exec)
// {
// 	if (exec->infile > 0)
// 		close(exec->infile);
// 	if (exec->outfile > 0)
// 		close(exec->outfile);
// }
void	init_exec(t_exec *exec)
{
	// exec->infile = -1;
	// exec->outfile = -1;
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
