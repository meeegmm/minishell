#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"

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
	tab[0] = "cd";
	tab[1] = "env";
	tab[2] = "pwd";
	tab[3] = "echo";
	tab[4] = "unset";
	tab[5] = "export";
	while (str[i] && i <= 5)
	{
		if (ft_strcmp(str, tab[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
