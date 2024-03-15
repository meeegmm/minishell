#include "../inc/parsing.h"

t_group *parser(char *line, char **envp) //или эта функция, или get_group избыточная
{
	char **token_tab;
	t_tokens *token_list;
	t_group *group;
	
	if(only_spaces(line))
		return(invalid_group(256)); //is this number ok?

	line = remove_quotes(line);
	if(line == NULL)
		return (NULL); //malloc pb or unclosed quotes

	printf("line after remove_quotes and expand: %s\n", line);

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
	{
		perror("tokens");
		return (NULL); //malloc pb
	}

	// to check the REDIR syntax here //
		//if(syntax_pb(token_tab) != 0)
			// group = invalid_group(); (bash: syntax error near unexpected token `>>')

	token_list = lexer(token_tab);
	if(token_list == NULL)
	{
		printf("Problem"); //malloc pb
		return (NULL);
	}
	else
	{
		printf("Token list:\n");
		print_token_list(token_list);
		printf("\n");
		group = get_group(token_list, envp); //shoudn't work for non-existing cmd
		//free_tokens(list);
	}
	return (group);
}