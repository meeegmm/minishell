#include "../../inc/exec.h"

void	ft_putstr_fd(char *cmd, char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	write(fd, cmd, ft_strlen(cmd));
	write(fd, ": ", 2);
	write(fd, s, i);
	write(fd, ": ", 2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
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

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

//not used
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

