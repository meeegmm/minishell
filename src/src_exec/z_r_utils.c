#include "../../inc/exec.h"

void	redir_in_b(t_exec *exec, t_group *group, t_built *fd)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	exec->fd_in = open(group->redir_in, O_RDONLY | S_IRWXU);
	fd->in = exec->fd_in;
	// dup2(exec->fd_in, 0);
	// close(exec->fd_in);
}

void	redir_out_b(t_exec *exec, t_group *group, t_built *fd)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->redir_out, \
						O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	fd->out = exec->fd_out;
	// dup2(exec->fd_out, 1);
	// close(exec->fd_out);
}

void	append_out_b(t_exec *exec, t_group *group, t_built *fd)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->app_out, O_APPEND | S_IRWXU);
	fd->out = exec->fd_out;
	// dup2(exec->fd_out, 1);
	// close(exec->fd_out);
}
void	ft_redir_b(t_exec *exec, t_group *group, t_built *fd)
{
	if (group->redir_in != NULL)
		redir_in_b(exec, group, fd);
	else if (group->redir_out != NULL)
		redir_out_b(exec, group, fd);
	else if (group->app_out != NULL)
		append_out_b(exec, group, fd);
}
