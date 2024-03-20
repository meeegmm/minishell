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
