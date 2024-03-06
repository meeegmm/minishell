#include "../../inc/exec.h"

//not for bultins
//browse list and check for pipes
//1 simple cmd
//2 background exec (fork()), redir
//3 pipes
void	ft_exec(t_group *group, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid)
		wait(NULL);
	else if (execve(group->cmd[0], group->cmd, envp) == 0)
	{
		if (access(group->cmd[0], F_OK) == -1)
			perror("Access denied");
		else
			perror("Exit");
	}
}
