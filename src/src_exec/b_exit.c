#include "../../inc/exec.h"

//end the process
//process then only contain return status
//go to parent or end shell

void	builtin_exit(t_exec *exec, t_group *group)
{
	if (exec->status == 0)
		exit(EXIT_SUCCESS);
	else if (exec->status == 2)
	{
		ft_putstr_fd("minishell", group->cmd[0], 2);
		//too many arguments
		// exit(EXIT_FAILURE);
	}
	else if (exec->status == 3)
	{
		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
		//wrong path
		// exit(EXIT_FAILURE);
	}
	else if (exec->status == 4)
	{
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
		// exit(EXIT_FAILURE);
	}
	else if (exec->status == 5)
	{
		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
		// //invalid option
		// exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}