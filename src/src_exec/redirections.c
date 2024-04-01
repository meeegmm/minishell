#include "../../inc/exec.h"

//!! si redir = deja fork
//always connect before I/O redir
//open then dup(2)
//do it for all redir
//exec

void	redir_in(t_exec *exec, t_group *group)
{
	close(exec->infile);
	exec->infile = open(group->redir_in, O_RDONLY | S_IRWXU);
	if (exec->infile == -1)
	{
		//errors
		return ;
	}
	dup2(exec->infile, STDIN_FILENO);
}

void	redir_out(t_exec *exec, t_group *group)
{
	close(exec->outfile);
	exec->outfile = open(group->redir_out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (exec->outfile == -1)
	{
		//errors
		return ;
	}
	dup2(exec->outfile, STDOUT_FILENO);
}

void	append_out(t_exec *exec, t_group *group)
{
	close(exec->outfile);
	exec->outfile = open(group->app_out, O_APPEND | S_IRWXU);
	if (exec->outfile == -1)
	{
		//errors
		return ;
	}
	dup2(exec->outfile, STDOUT_FILENO);
}
