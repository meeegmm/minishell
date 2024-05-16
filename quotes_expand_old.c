/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:12:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/12 23:45:17 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

char *quotes_expand(char *str, t_list_env *env)
{
	char *spaces_quotes_replaced;
	char *no_double;
	char *no_single;
	char *expnd;

	spaces_quotes_replaced = NULL;
	no_double = NULL;
	no_single = NULL;
	expnd = NULL;
	
	spaces_quotes_replaced = add_spaces(&str);
	if(spaces_quotes_replaced == NULL)
		return (NULL);
	no_double = no_quotes(spaces_quotes_replaced, 29);
	if(no_double == NULL || *no_double == '\0') //en vrai c'est cmd not found
	{
		free(spaces_quotes_replaced);
		if(no_double)
			free(no_double);
		return (NULL);
	}
	expnd = ft_expand(no_double, env);
	if(expnd == NULL || *expnd == '\0') //en vrai c'est cmd not found
	{
		free(spaces_quotes_replaced);
		free(no_double);
		if(expnd)
			free(expnd);
		return (NULL);
	}
	no_single = no_quotes(expnd, 30);
	if(no_single == NULL || *no_single == '\0') //en vrai c'est cmd not found
	{
		free(spaces_quotes_replaced);
		free(no_double);
		free(expnd);
		if(no_single)
			free(no_single);
		return (NULL);
	}
	if(no_double)
		free(no_double);
	if(spaces_quotes_replaced)
		free(spaces_quotes_replaced);
	if(expnd)
		free(expnd);
	return(no_single);
}
