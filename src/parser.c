#include "../inc/parsing.h"

t_group *parser(char *input, t_list_env *env)
{
	char **token_tab;
	t_tokens *token_list;
	t_group *group;
	char *line;
	
	if(only_spaces(input))
		return(invalid_group(2));

	line = quotes_expand(input, env);
	if(line == NULL)
	{
		return (invalid_group(2)); //malloc pb or unclosed quotes
	}

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

	if(syntax_pb(token_list))
	{
		free(line);
		free_tab(token_tab);
		free_tokens(token_list);
		return(invalid_group(2));
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