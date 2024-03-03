#include "../../inc/exec.h"

void	ft_exec(t_group *group, char **envp)
{
	pid_t	pid;

	pid = fork();

	if (pid)
		wait(NULL);
	else
		if (execve(group->cmd[0], group->cmd, envp) == 0)
		{
			if (access(group->cmd[0], F_OK) == -1)
				perror("Access denied");
			else
				perror("Exit");
		}
}