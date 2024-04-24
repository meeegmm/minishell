#include "../../inc/exec.h"

//add printf
//add checks
//think about exit
int	ft_bin(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	char	**envp;
	pid_t	pid;

	envp = get_envp(env_lst);
	pid = fork();
	if (pid == -1)
		perror("Error exec fork"); // return value?
	exec->pid = pid;
	if (exec->pid == 0)
	{
		if (execve(group->cmd[0], group->cmd, envp) == 0)
		{
			if (access(group->cmd[0], F_OK | X_OK) == -1)
			{
				free_tab(envp);
				return(2);
			}
		}
	}
	else
		waitpid(-1, NULL, 0);
	free_tab(envp);
	return (0);
}

void	simple_cmd(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	if (exec->pid == -1 && group_size(group) == 1)
	{
		if (is_built2(group->cmd[0]))
			exec->status = ft_builtins(exec, group, env_lst);
		else
			exec->status = ft_bin(exec, group, env_lst);
		return ;
	}
	else if (is_built2(group->cmd[0]))
	{
		// waitpid(exec->pid, NULL, 0);
		exec->status = ft_builtins(exec, group, env_lst);
	}
	else
		exec->status = ft_bin(exec, group, env_lst);
	return ;
}
