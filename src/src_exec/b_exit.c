#include "../../inc/exec.h"

//end the process
//process then only contain return exec->status
//go to parent or end shell

void	end_minish(t_exec *exec, t_group *start, t_list_env *env)
{
	free_group_list(start);
	free_envp_list(env);
	close_fds(exec);
	close_std(exec);
	rl_clear_history();
}

void	builtin_exit(t_exec *exec, t_group *group, t_list_env *env)
{
	if (exec->status == 0)
	{
		// printf("SUCCES exec->status: %d\n", exec->status);
		end_minish(exec, group, env);
		exit(EXIT_SUCCESS);
	}
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
	// printf("FAIL exec->status: %d\n", exec->status);
	end_minish(exec, group, env);
	exit(EXIT_FAILURE);
}