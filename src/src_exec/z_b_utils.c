#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"


char	*set_dir(t_list_env *env_lst, char *key)
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

//v2
// char	*set_dir(t_list_env *env_lst, char *path)
// {
// 	char	*res;
//
// 	while (env_lst != NULL)
// 	{
// 		if (ft_strcmp(env_lst->key, path) == 0)
// 		{
// 			res = ft_strdup(env_lst->value);
// 			return (res);
// 		}
// 		else
// 			env_lst = env_lst->next;
// 	}
// 	return (path);
// }

//not used
char	*mod_var(t_list_env *env_lst, char *key, char *new)
{
	t_list_env	*head;
	char		*res;

	head = env_lst;
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, new) == 0)
		{
			res = ft_strdup(env_lst->value);
			break ;
		}
		else
			env_lst = env_lst->next;
	}
	env_lst = head;
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
		{
			env_lst->value = ft_strdup(res);
			return (env_lst->value);
		}
		else
			env_lst = env_lst->next;
	}
	return (NULL);
}

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
		if (ft_strcmp(str, tab[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
