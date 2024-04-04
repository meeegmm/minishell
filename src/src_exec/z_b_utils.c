#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"

//get path from varname
char	*set_path(t_list_env *env_lst, char *key)
{
	char	*path;

	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
		{
			path = ft_strdup(env_lst->value);
			return (path);
		}
		else
			env_lst = env_lst->next;
	}
	return (NULL);
}

//changed
int	is_built(char *str)
{
	int		i;
	char	*tab[6];

	i = 0;
	tab[0] = "cd";
	tab[1] = "env";
	tab[2] = "pwd";
	tab[3] = "echo";
	tab[4] = "unset";
	tab[5] = "export";
	while (str[i] && i <= 5)
	{
		if (ft_strncmp(str, tab[i], ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_builtins(t_group *group, t_list_env *env_lst)
{
	if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
		builtin_cd(group, group->cmd[1], env_lst);
	else if (ft_strncmp(group->cmd[0], "env", 3) == 0)
		builtin_env(group, env_lst);
	else if (ft_strncmp(group->cmd[0], "pwd", 3) == 0)
		builtin_pwd(group);
	else if (ft_strncmp(group->cmd[0], "echo", 4) == 0)
		builtin_echo(group);
	else if (ft_strncmp(group->cmd[0], "unset", 5) == 0)
		builtin_unset(group, env_lst);
	else if (ft_strncmp(group->cmd[0], "export", 6) == 0)
		builtin_export(group, env_lst);
	else
		return ;
}