/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:00 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/20 17:02:15 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	is_folder(char *line)
{
	int	fd;
	int	res;
	DIR	*d;

	if(!line || *line == '\0')
		return (0);
	fd = open(line, O_WRONLY); //???????
	d = opendir(line);
	if (fd == -1 && d != NULL)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(line);
		ft_putstr_err(": Is a directory\n");
		res = 1;
	}
	else
		res = 0;
	if (fd > 0)
		close(fd);
	if (d)
		closedir(d);
	return (res);
}

t_parser	*create_init_p(void)
{	
	t_parser	*p;

	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	init_t_parser(p);
	return (p);
}

t_group	*create_init_group(void)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group || group == NULL)
		return (NULL);
	invalid_group(group, 0);
	return (group);
}

char	**spaces_between_quotes(char ***tab)
{
	int	i;
	int	k;

	i = 0;
	while ((*tab)[i])
	{
		k = 0;
		while ((*tab)[i][k] != '\0')
		{
			if ((*tab)[i][k] == 27)
				(*tab)[i][k] = ' ';
			k++;
		}
		i++;
	}
	return (*tab);
}
