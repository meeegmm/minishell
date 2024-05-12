/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:32:23 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/11 03:14:20 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int quotes_ok(char **str)
{
	int i;
	int res;
	int start;

	i = 0;
	res = 1;
	while((*str)[i])
	{
		if((*str)[i] == '"')
		{
			res = 0;
			start = i;
			while((*str)[i])
			{
				i++;
				if((*str)[i] == '"')
				{
					res = 1;
					(*str)[start] = 29;
					if(start > 0 && (*str)[start - 1] == '$')
						(*str)[start] = 30;					// !!!!!! TO FIX IT
					(*str)[i] = 31;
					break;
				}
			}
		}
		else if((*str)[i] == '\'')
		{
			res = 0;
			start = i;
			while((*str)[i])
			{
				i++;
				if((*str)[i] == '\'')
				{
					res = 1;
					(*str)[start] = 30;
					(*str)[i] = 31;
					break;
				}
			}
		}
		if((*str)[i])
			i++;
	}
    return (res);
}