#include "../../inc/exec.h"

void	init_std(t_exec *exec)
{
	exec->std_in = dup(STDIN_FILENO);
	exec->std_out = dup(STDOUT_FILENO);
}

void	reset_std(t_exec *exec)
{
	exec->std_in = dup2(exec->std_in, STDIN_FILENO);
	exec->std_out = dup2(exec->std_out, STDOUT_FILENO);
}

void	init_exec(t_exec *exec)
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

// t_exec	init_exec(void)
// {
// 	t_exec	exec;

// 	exec.infile = -1;
// 	exec.outfile = -1;
// 	exec.pfd_in = -1;
// 	exec.pfd_out = -1;
// 	exec.pid = -1;
// 	return (exec);
// }