#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"

//set_env function
char	*set_dir(char *path)
{
	path = getenv(path);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	return ("error");
}

int	is_built(char *str)
{
	int		i;
	char	*tab[6];

	i = 0;
	tab[0] = "echo";
	tab[1] = "cd";
	tab[2] = "pwd";
	tab[3] = "export";
	tab[4] = "unset";
	tab[5] = "env";
	while (str[i])
	{
		if (ft_strcmp(tab[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}
