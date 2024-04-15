#include "../../inc/exec.h"

//voir pour le prmier node
//okay dans la fonction mais modifeir **env_lst pour aller au next

int	builtin_unset(t_group *group, t_list_env *env_lst)
{
	int	i;
	t_list_env	*tmp;

	i = 1;
	tmp = env_lst;
	if (ft_strncmp(group->cmd[0], "unset", 5) == 0)
	{
		if (tab_size(group->cmd) == 1)
			return (0);
		else
		{
			while (group->cmd[i])
			{
				if (ft_strncmp(env_lst->key, get_key(group->cmd[i]), \
												ft_strlen(group->cmd[i])) != 0)
				{
					env_lst = check_var(&env_lst, group->cmd[i]);
					remove_var(&env_lst);
				}
				else
				{
					remove_first(&env_lst);
					tmp = env_lst;
				}
				env_lst = tmp;
				printf("\n\n");
				print_env_list(env_lst);
				i++;
			}
		}
		return (0);
	}
	else
		// ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}