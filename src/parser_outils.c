/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:00 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/29 18:48:37 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	only_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

t_parser	*create_init_p(void)
{	
	t_parser	*p;

	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->line = NULL;
	p->token_tab = NULL;
	p->token_list = NULL;
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

void	invalid_group(t_group *group, int flag)
{
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->app_in = NULL;
	group->next = NULL;
}
