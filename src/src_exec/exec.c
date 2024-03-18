#include "../../inc/exec.h"

//!! si redir = deja fork
//not for bultins
//browse line and check for pipes
//get index of pipe
//group before and after
//add dup function
//1 simple cmd
//2 background exec (fork()), redir
//3 pipes

void	ft_s_exec(t_group *group, char **envp)
{
	pid_t	pid;
	// // if (!group->cmd)
	// // {
	// // 	ft_putstr_fd("minishell", cmd, 2);
	// // 	//cmd not found
	// // 	return ;
	// // }
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
