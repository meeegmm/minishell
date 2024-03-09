#include "../../inc/exec.h"

void	ft_putstr_fd(char *cmd, char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	write(fd, cmd, ft_strlen(cmd));
	write(fd, s, i);
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
