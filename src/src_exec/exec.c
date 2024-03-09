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
		ft_putstr_fd(cmd, ": Command not found\n", 2);
		strerror(127);
		return ;
	}
	pid = fork();
	if (pid)
		wait(NULL);
	else if (execve(group->cmd[0], group->cmd, envp) == 0)
	{
		if (access(group->cmd[0], F_OK) == -1)
		{
			perror("Access denied");
			return ;
		}
		else
			perror("Exit");
	}
}

void	simple_cmd(t_tokens *token_lst, t_group *group, char **envp)
{
	if (!is_built(token_lst->value))
		ft_builtins(token_lst, group, envp);
	else
		ft_s_exec(token_lst, group, envp);
}
