#include "../../inc/exec.h"

//not for bultins
//browse line and check for pipes
//get index of pipe
//group before and after
//add dup function
//1 simple cmd
//2 background exec (fork()), redir
//3 pipes

void	ft_s_exec(t_tokens *token_lst, t_group *group, char **envp)
{
	char	*cmd;
	pid_t	pid;

	cmd = token_lst->value;
	if (!group->cmd[0])
	{
		ft_putstr_fd("minishell", cmd, 2);
		//cmd not found
		return ;
	}
	pid = fork();
	if (pid)
		wait(NULL);
	else if (execve(group->cmd[0], group->cmd, envp) == 0)
	{
		if (access(group->cmd[0], F_OK | X_OK) == -1)
		{
			ft_putstr_fd(cmd, group->cmd[0], 2);
			perror(NULL);
		}
	}
}

void	simple_cmd(t_tokens *token_lst, t_group *group, char **envp)
{
	if (!is_built(token_lst->value))
		ft_builtins(token_lst, group, envp);
	else
		ft_s_exec(token_lst, group, envp);
}
