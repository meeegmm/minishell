#include "../inc/parsing.h"

int syntax_pb(t_tokens *list)
{
	if(list->type == 5)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while(list != NULL)
	{
		if(list->type >= 1 && list->type <= 4 && list->next != NULL && list->next->type != 0) //to think abt app_in (heredoc)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", list->value);
			return (1);
		}
		if(list->type != 0 && list->next != NULL && list->next->type == 5)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", list->value);
			return (1);
		}
		if(list->type != 0 && list->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}

t_group *parser(char *line, char **envp)
{
	char **token_tab;
	t_tokens *token_list;
	// t_tokens *start;
	t_group *group;
	
	if(only_spaces(line))
		return(invalid_group(2)); //is this number ok?

	line = remove_quotes(line);
	if(line == NULL)
		return (invalid_group(2)); //malloc pb or unclosed quotes

	printf("no quotes + expand: %s\n", line); //do expand

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
		return (NULL); //malloc pb

	token_list = lexer(token_tab);
	if(token_list == NULL)
	{
		//free_tab(token_tab);
		return (NULL); //malloc pb	
	}
	// start = token_list;

	printf("Token list:\n");
	print_token_list(token_list);
	printf("\n");

	// token_list = start;
	free_tab(token_tab);
	if(syntax_pb(token_list))
	{
		free_tokens(token_list);
		return(invalid_group(2));
	}
	// printf("here%s", start->value);
	// token_list = start;
	group = get_group_list(token_list, envp);
	free_tokens(token_list);
	return (group);
}