#include "../../inc/exec.h"

//add dup function
//1 simple cmd
//2 pipes
//3 background exec (fork()), redir

void	ft_s_exec(t_group *group, char **envp)
{
	pid_t	pid;
	if (group->flag_fail)
	{
		ft_putstr_fd("minishell", "error", 2);
		write(2, "Command not found\n", 18);
		return ;
	}
	pid = fork();
	if (pid)
		wait(NULL);
	else if (execve(group->cmd[0], group->cmd, envp) == 0)
	{
		if (access(group->cmd[0], F_OK | X_OK) == -1)
		{
			ft_putstr_fd("minishell", group->cmd[0], 2);
			perror(NULL);
		}
	}
}

void	simple_cmd(t_group *group, t_list_env *env_lst, char **envp)
{
	if (is_built(group->cmd[0]))
		ft_builtins(group, env_lst);
	else
		ft_s_exec(group, envp);
}
