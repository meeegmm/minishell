#include "../../inc/exec.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
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

int	open_file(char *file, int std_no)
{
	int	opnd_fd;

	if (std_no == 0)
		opnd_fd = open(file, O_RDONLY, 0644);
	if (std_no == 1)
		opnd_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (opnd_fd == -1)
		exit(0);
	return (opnd_fd);
}
