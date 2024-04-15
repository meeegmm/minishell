#include "../../inc/exec.h"

// change $OLDPWD

int	builtin_cd(t_group *group, char *path, t_list_env *env_lst)
{
	if (tab_size(group->cmd) > 2)
	{
		// ft_putstr_fd("minishell", group->cmd[0], 2);
		//too many arguments
		return (2);
	}
	if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
	{
		if (tab_size(group->cmd) == 1 \
			|| ft_strncmp(group->cmd[1], "~", 1) == 0)
			path = set_path(env_lst, "HOME");
		else if (ft_strncmp(group->cmd[1], "-", 1) == 0)
		{
			path = set_path(env_lst, "OLDPWD");
			ft_putstr(path);
			write(1, "\n", 1);
		}
		if (chdir(path) == -1)
		{
			// ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
			// perror(NULL);
			return (3);
		}
		//$OLDPWD = path
		return (0);
	}
	// ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}
