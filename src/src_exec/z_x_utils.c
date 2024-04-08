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

void	init_exec(t_exec *exec)
{
	exec->std_in = -1;
	exec->std_out = -1;
	exec->pfd_in = -1;
	exec->pfd_out = -1;
	exec->pid = -1;
}

void	close_fds(t_exec *exec)
{
	if (exec->std_in > 0)
		close(exec->std_in);
	if (exec->std_out > 0)
		close(exec->std_out);
	if (exec->pfd_in > 0)
		close(exec->pfd_in);
	if (exec->pfd_out > 0)
		close(exec->pfd_out);
}
