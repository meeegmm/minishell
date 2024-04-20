#include "../../inc/exec.h"

int	builtin_export(t_group *group, t_list_env *env_lst)
{
	int			i;
	t_list_env	*tmp;

	i = 1;
	tmp = env_lst;
	if (ft_strncmp(group->cmd[0], "export", 3) == 0)
	{
		if (tab_size(group->cmd) == 1)
		{
			while (env_lst != NULL)
			{
				printf("export %s=\"%s\"\n", env_lst->key, env_lst->value);
				env_lst = env_lst->next;
			}
			return (0);
		}
		else
		{
			while (group->cmd[i])
			{
				// printf("key = %s\n", env_lst->key);
				// printf("\n\n\n");
				if (ft_strncmp(env_lst->key, get_key(group->cmd[i]), \
												ft_strlen(env_lst->key) != 0))
					env_lst = check_var(&env_lst, group->cmd[i]);
				// printf("key = %s\n", env_lst->key);
				// printf("\n\n\n");
				mod_var(&env_lst, group->cmd[i]);
				env_lst = tmp;
				i++;
			}
		}
		return (0);
	}
	else
		// ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}