#include "../../inc/exec.h"

//function is_option?
// echo \n word = \n word (sgould not print \)

int	builtin_echo(t_group *group)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (ft_strncmp(group->cmd[0], "echo", 4) == 0)
	{
		if (tab_size(group->cmd) < 2)
		{
			write(1, "\n", 1);
			return (0);
		}
		i++;
		while (group->cmd[i])
		{
			if (ft_strncmp(group->cmd[i], "-n", 2) == 0 \
											&& is_char(group->cmd[i], 'n'))
			{
				option = 1;
				i++;
			}
			else
				break ;
		}
		//write on exec->fd_out?
		while (group->cmd[i])
		{
			ft_putstr(group->cmd[i]);
			if (group->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (!option)
			write(1, "\n", 1);
		return (0);
	}
	else
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}
