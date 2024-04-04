#include "../../inc/minishell.h"
#include "../../inc/exec.h"

//1 simple cmd
//2 pipes
//3 background exec (fork()), redir

void	ft_bin(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	char	**envp;
	pid_t	pid;

	envp = get_envp(env_lst);
	if (group->flag_fail)
	{
		ft_putstr_fd("minishell", "error", 2);
		write(2, "Command not found\n", 18);
		return ;
	}
	if (exec->pid != -1)
		pid = exec->pid;
	else
		pid = fork();
	if (pid == 0)
	{
		if (execve(group->cmd[0], group->cmd, envp) == 0)
		{
			if (access(group->cmd[0], F_OK | X_OK) == -1)
			{
				ft_putstr_fd("minishell", group->cmd[0], 2);
				perror("exec");
				//exit
			}
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	simple_cmd(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	if (group->flag_fail)
		//exit
		return ;
	if (is_built(group->cmd[0]))
		ft_builtins(group, env_lst);
	else
		ft_bin(exec, group, env_lst);
}

void	ft_exec(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	if (group->redir_in != NULL)
		redir_in(exec, group);
	else if (group->redir_out != NULL)
		redir_out(exec, group);
	else if (group->app_out != NULL)
		append_out(exec, group);
	if (group_size(group) > 1)
	{
		ft_pipe(exec);
		ft_exec(exec, group->next, env_lst);
	}
	simple_cmd(exec, group, env_lst);	
}