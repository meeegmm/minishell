/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:12:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/20 14:24:03 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int is_meta(char *str)
{
	return(*str == '|' || *str == '<' || *str == '>');
}

int is_meta_move(char **str)
{
	if(is_meta(*str) > 0)
	{
		if((**str == '>' || **str == '<') && *(*str + 1) && (**str == *(*str + 1)))
			(*str)++;
		(*str)++;
		return (1);
	}
	return (0);
}

char *quotes_ok(char *str) //faire plus court
{
	int i;
	int res;
	int start;

	i = 0;
	res = 1;
	while(str[i])
	{
		if(str[i] == '"')
		{
			res = 0;
			start = i;
			while(str[i])
			{
				i++;
				if(str[i] == '"')
				{
					res = 1;
					str[start] = 'D';
					if(start > 0 && str[start - 1] == '$')
						str[start] = 'S';
					str[i] = 'Z';
					break;
				}

			}
		}
		else if(str[i] == '\'')
		{
			res = 0;
			start = i;
			while(str[i])
			{
				i++;
				if(str[i] == '\'') //don't do expand inside
				{
					res = 1;
					str[start] = 'S';
					str[i] = 'Z';
					break;
				}
			}
		}
		if(str[i])
			i++;
	}
	if(res == 0)
	{
		ft_putstr_err("Invalid syntax: unclosed quotes\n");
		return (NULL); //подумать, как записать это во flag_fail
	}
	else
		return (str);
}

int ending_quotes_nb(char *str)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == 'Z')
			len++;
		i++;
	}
	return (len);
}

char *with_28(char ***str)
{
	int i;
	int len;
	char *new;
	int l;

	i = 0;
	len = 0;
	printf("HERE NB of Z : %d\n", ending_quotes_nb(**str));
	l = ft_strlen(**str) + ending_quotes_nb(**str) + 1;
	printf("HERE l %d\n", l);
	new = malloc(sizeof(char) * l);
	if(!new)
		return (NULL); //???
	while(i + 1 < l && (**str)[len])
	{
		new[i] = (**str)[len];
		i++;
		if((**str)[len] == 'Z' && i < l)
		{
			new[i] = 'X'; //change to 28
			i++;	
		}
		len++;
	}
	new[i] = '\0';
	// free((**str));
	// (**str) = new;
	// free(new);
	return (new);
}

int spaces_nb(char *str)
{
	int counter;
	
	counter = 0;
	while(*str)
	{
		if(is_meta_move(&str) > 0)
			counter++;
		else
			str++;
	}
	return (counter * 2);
}

void hide_spaces_between_quotes(char **str) //make void?
{
	int i;

	i = 0;
	while((*str)[i])
	{
		if((*str)[i] == 'D' || (*str)[i] == 'S')
		{
			while((*str)[i] && (*str)[i] != 'Z')
			{
				if((*str)[i] == ' ' || (*str)[i] == '\t')
					(*str)[i] = 27;
				i++;
			}
		}
		if((*str)[i])
			i++;
	}
}

char *add_spaces(char **tmp)
{
	char *new_str;
	char *str;
	char *start;
	int len;
	int i;
	
	i = 0;
	*tmp = quotes_ok(*tmp);
	if(*tmp == NULL)
		return (NULL);
	str = with_28(&tmp);
	start = str;
	
	printf("AFTER +X after ending quotes: %s\n", str);

	hide_spaces_between_quotes(&str);
	// printf("HERE spaces are hidden %s\n", str);

	len = spaces_nb(str) + ft_strlen(str) + 1;

	new_str = malloc(sizeof(char) * (len + 1));
	if(!new_str)
	{
		free(str);
		return (NULL);
	}

	while(i < len && *str)
	{
		if(*str == 'D' || *str == 'S')
		{
			while(*str && *str != 'Z' && i < len)
			{
				new_str[i] = *str;
				(str)++;
				i++;
			}
			if(*str && i < len)
			{
				new_str[i] = *str;
				(str)++;
				i++;
			}
			// printf("HERE spaces are hidden %s\n", str);
		}
		if(*str && (is_meta(str) > 0) && (i + 2 < len))
		{
			new_str[i] = ' ';
			new_str[i + 1] = *str;
			if(*str != '|' && (*str == *((str) + 1)))
			{
				new_str[i + 2] = *((str) + 1);
				(str)++;
				if(i + 3 < len)
					i++;
			}
			(str)++;
			new_str[i + 2] = ' ';
			i += 3;
		}
		new_str[i] = *str;
		if(i < len)
			i++;
		if(*str)
			(str)++;
	}
	new_str[i] = '\0';
	free((start));
	// (str) = new_str;
	// free(new_str);
	return (new_str);
}

int quotes_nb(char *str, char c)
{
	int nb;

	nb = 0;
	while(*str)
	{
		if(*str == c)
			nb++;
		str++;
	}
	// printf("quotes_nb %d\n", nb * 2);
	return (nb * 2);
}

char *no_quotes(char *str, char c)
{
	char *new;
	int i;
	int k;
	int len;
	
	i = 0;
	k = 0;

	if(c == 'D')
		printf("NB of double quotes: %d\n", quotes_nb(str, c));
	if(c == 'S')
		printf("NB of single quotes: %d\n", quotes_nb(str, c));

	len = ft_strlen(str) - quotes_nb(str, c) + 1;
	new = malloc(sizeof(char) * len);
	if(!new)
		return NULL;

	while(str[i] && k < len)
	{
		if(str[i] == c)
		{
			i++;
			while(str[i] && str[i] != 'Z' && k < len) //check if str[i - 1] != '$'
			{
				new[k] = str[i];
				k++;
				i++;
			}
			if(str[i] && str[i] == 'Z')
				i++;
		}
		if(str[i] && str[i] != c && k < len)
		{
			new[k] = str[i];
			k++;
			i++;
		}
		else
			continue ;
	}
	new[k] = '\0';
	return (new);
}

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
	
	spaces_quotes_replaced = add_spaces(&str); //IT SHOULDNt FREE STR!
	// printf("spaces_quotes_replaced : %s\n", spaces_quotes_replaced);
	
	if(spaces_quotes_replaced == NULL)
		return (NULL);
	
	no_double = no_quotes(spaces_quotes_replaced, 'D');
	printf("no_double : %s\n", no_double);

	if(no_double == NULL || *no_double == '\0') //en vrai c'est cmd not found
	{
		free(spaces_quotes_replaced);
		if(no_double)
			free(no_double);
		return (NULL);
	}
	
	expnd = ft_expand(no_double, env);
	printf("expand done : %s\n", expnd);
	if(expnd == NULL || *expnd == '\0') //en vrai c'est cmd not found
	{
		free(spaces_quotes_replaced);
		free(no_double);
		if(expnd)
			free(expnd);
		return (NULL);
	}
	
	no_single = no_quotes(expnd, 'S');
	printf("no_single : %s\n", no_single);

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