#include "../../inc/exec.h"

void	init_fds(t_exec *exec)
{
	exec->infile = -1;
	exec->outfile = -1;
	exec->pfd_in = -1;
	exec->pfd_out = -1;
	exec->pid = -1;
}

void	close_fds(t_exec *exec)
{
	if (exec->infile > 0)
		close(exec->infile);
	if (exec->outfile > 0)
		close(exec->outfile);
	if (exec->pfd_in > 0)
		close(exec->pfd_in);
	if (exec->pfd_out > 0)
		close(exec->pfd_out);
}

t_exec	init_exec(void)
{
	t_exec	exec;

	exec.infile = -1;
	exec.outfile = -1;
	exec.pfd_in = -1;
	exec.pfd_out = -1;
	exec.pid = -1;
	return (exec);
}