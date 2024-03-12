#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"

char	*set_dir(char *path)
{
	path = getenv(path);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	return (NULL);
}

int	is_char(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == c)
		i++;
	if (i == ft_strlen(str))
			return (1);
	else
		return (0);
}

void	print_token_lst(t_tokens *token_lst)
{
	while (token_lst != NULL)
	{
		printf("%s", token_lst->value);
		if (token_lst->next != NULL)
			printf(" ");
		token_lst = token_lst->next;
	}
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
