/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:09:37 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/27 02:17:31 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include "../../inc/minishell.h"

int	is_special(char c)
{
	return (!is_digit(c) && !is_alpha(c) && c != '*' && c != '#' && c != '?');
}

int	delimiter_nb(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || (is_special(str[i])) || str[i] == 30)
			nb++;
		if (str[i] == '$' && str[i + 1] && is_digit(str[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

t_tokenizer	*init_data(char *s)
{
	t_tokenizer	*d;

	d = malloc(sizeof(t_tokenizer));
	if (!d)
		return (NULL);
	d->i = 0;
	d->k = 0;
	d->len = delimiter_nb(s) + ft_strlen(s) + 1;
	d->new = malloc(sizeof(char) * d->len);
	if (!d->new)
		return (NULL);
	return (d);
}

void	between_single(t_tokenizer *d, char *s)
{
	d->new[d->k] = 28;
	d->k++;
	while (s[d->i] && s[d->i] != 31 && d->k < d->len)
	{
		d->new[d->k] = s[d->i];
		d->k++;
		d->i++;
	}
	if (d->k < d->len && s[d->i])
	{
		d->new[d->k] = 30;
		d->k++;
		d->i++;
	}
}
