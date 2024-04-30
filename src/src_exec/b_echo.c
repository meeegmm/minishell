/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:56:14 by memarign          #+#    #+#             */
/*   Updated: 2024/04/30 12:22:54 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//function is_option?
// echo \n word = \n word (sgould not print \)

int	check_option(char *str, char c)
{
	if (ft_strncmp(str, "-n", 2) == 0 \
									&& is_char(str, c))
		return (1);
	return (0);
}

int	builtin_echo(t_group *group)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (tab_size(group->cmd) < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	option = check_option(group->cmd[1], 'n');
	if (option)
		i++;
	while (group->cmd[i])
	{
		ft_putstr(group->cmd[i]);
		if (group->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!option)
	{
		write(1, "\n", 1);
	}
	return (0);
}
