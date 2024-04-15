#include "../../inc/exec.h"

int	builtin_pwd(t_group *group)
{
	size_t	size;
	char	*buf;
	char	*dir;

	size = 0;
	buf = NULL;
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strncmp(group->cmd[1], "-", 1) == 0 \
								&& !is_char(group->cmd[1], '-'))
		{
			// ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
			// //invalid option
			return (5);
		}
	}
	if (ft_strncmp(group->cmd[0], "pwd", 3) == 0)
	{
		dir = getcwd(buf, size);
		ft_putstr(dir);
		write(1, "\n", 1);
		free(buf);
		free(dir);
		return (0);
	}
	free(buf);
	// ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}