#include "../../inc/exec.h"

//!! si redir = deja fork
//always connect before I/O redir
//open then dup(2)
//do it for all redir
//exec

//doesn't create all files when multiple redir
//output = last redir output?

void	redir_in(t_exec *exec, t_group *group)
{
	if (exec->std_in > 0)
		close(exec->std_in);
	exec->std_in = open(group->redir_in, O_RDONLY | S_IRWXU);
	if (exec->std_in == -1)
	{
		//SIG
		perror("open");
		return ;
	}
	dup2(exec->std_in, STDIN_FILENO);
}

void	redir_out(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->redir_out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (exec->fd_out == -1)
	{
		//SIG
		perror("open");
		return ;
	}
	dup2(exec->fd_out, STDOUT_FILENO);
}

void	append_out(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->app_out, O_APPEND | S_IRWXU);
	if (exec->fd_out == -1)
	{
		//SIG
		return ;
	}
	dup2(exec->fd_out, STDOUT_FILENO);
}
