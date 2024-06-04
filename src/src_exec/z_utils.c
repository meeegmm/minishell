/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madmeg <madmeg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 04:06:33 by memarign          #+#    #+#             */
/*   Updated: 2024/05/22 13:31:59 by madmeg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
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

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > 32)
			return (1);
		i++;
	}
	return (0);
}
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n-- > 0)
		*(ptr++) = c;
	return (s);
}


