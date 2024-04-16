/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:51 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/16 21:56:48 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

t_group *invalid_group2(int flag)
{
	t_group *group;
	group = malloc(sizeof(t_group));
	if(!group || group == NULL)
		return (NULL);
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->app_in = NULL;
	group->next = NULL;
	return (group);
}

int is_folder(char *line)
{
	int fd;
	DIR *d;
	int res;

	fd = open(line, O_WRONLY);
	d = opendir(line);
	if(fd == -1 && d != NULL)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(line);
		ft_putstr_err(": Is a directory\n");
		res = 1;
	}
	else
		res = 0;
	if(fd > 0)
		close(fd);
	if(d)
		closedir(d);
	return (res);
}

t_group *parser(char *input, t_list_env *env)
{
	char **token_tab;
	t_tokens *token_list;
	t_group *group;
	char *line;
	
	if(only_spaces(input))
		return (invalid_group2(2));
	if(is_folder(input))
		return (invalid_group2(126));
	line = quotes_expand(input, env);
	if(line == NULL)
		return (invalid_group2(2)); //malloc pb or unclosed quotes

	printf("no quotes + expand: %s\n", line);

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
	{
		free(line);
		return (NULL); //malloc pb
	}
	token_list = lexer(token_tab);
	if(token_list == NULL)
	{
		free(line);
		free_tab(token_tab); //??
		return (NULL); //malloc pb	
	}

	printf("Token list:\n");
	print_token_list(token_list);
	printf("\n");

	if(syntax_pb(token_list)) //may it cause pb for some syntax pb (?)
	{
		free(line);
		free_tab(token_tab);
		free_tokens(token_list);
		return(invalid_group2(2));
	}
	else
	{
		group = get_group_list(token_list, env);
		// free_tokens(token_list); 				надо бы раскомментить
	}
	if(line)
		free(line);
	free_tab(token_tab);
	return (group);
}