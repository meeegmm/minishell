#include "../../inc/exec.h"

int	builtin_env(t_group *group)
{
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strcmp(group->cmd[1], "env") != 0)
		{
			// ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
			// write(2, "Too many arguments\n", 19);
			return (2);
		}
	}
	if (ft_strncmp(group->cmd[0], "env", 3) == 0)
	{
		// print_env_list(env_lst);
		return (0);
	}
	else
		// ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}