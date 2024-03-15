#include "../inc/parsing.h"

t_tokens *lexer(char **token_tab)
{
	int i;
	t_tokens *begin;
	t_tokens *curr;

	begin = malloc(sizeof(t_tokens));
	if (!begin)
		return (NULL);
	begin->type = WORD;
	begin->value = token_tab[0];
	begin->next = NULL;
	curr = begin;
	i = 1;
	while(token_tab[i] != NULL)
	{
		curr->next = malloc(sizeof(t_tokens));
		if(!curr->next)
		{
			//free_token_list(begin);
			free_tab(token_tab);
			return (NULL);
		}
		curr = curr->next;
		curr->value = token_tab[i];
		if(curr->value == "|")
			curr->type = PIPE;
		else if(curr->value == "<")
			curr->type = REDIR_IN;
		else if(curr->value == ">")
			curr->type = REDIR_OUT;
		else if(curr->value == "<<")
			curr->type = APP_IN;
		else if(curr->value == ">>")
			curr->type = APP_OUT;
		else
			curr->type = WORD;
		curr->next = NULL;
		i++;
	}
	return (begin);
}

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
		group = get_group(token_list, envp); //shoudn't work for non-existing cmd
		//free_tokens(list);
	}
	return (group);
}