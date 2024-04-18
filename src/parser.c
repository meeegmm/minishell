/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:51 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/18 20:32:39 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void invalid_group(t_group *group, int flag)
{
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->app_in = NULL;
	group->next = NULL;
}

void init_t_parser(t_parser *p)
{
	p->line = NULL;
	p->token_tab = NULL;
	p->token_list = NULL;
}

t_group *parser(char *input, t_list_env *env)
{
	t_parser *p;
	t_group *group;

	p = create_init_p();
	group = create_init_group();
	if(is_folder(input))
	{
		free_t_parser(p);
		invalid_group(group, 126);
		return (group);
	}
	p->line = quotes_expand(input, env);
	if(p->line == NULL)
	{
		invalid_group(group, 2);
		return (group);
	}
	p->token_tab = ft_split1(p->line, 1);
	if(p->token_tab == NULL)
	{
		free_t_parser(p);
		return (NULL);
	}
	spaces_between_quotes(&(p->token_tab));
	p->token_list = lexer(p->token_tab);
	if(p->token_list == NULL)
	{
		free_t_parser(p);
		return (NULL);
	}
	printf("Token list:\n");
	print_token_list(p->token_list);
	printf("\n");
	if(syntax_pb(p->token_list))
	{
		free_t_parser(p);
		invalid_group(group, 2);
		return (group);
	}
	else
	{
		free(group);
		group = get_group_list(p->token_list, env);
	}
	free_t_parser(p);
	return (group);
}



// printf("no quotes + expand: %s\n", p->line);

// printf("Token list:\n");
// print_token_list(p->token_list);
// printf("\n");