#include "../inc/parsing.h"

t_tokens *get_node(char **token_tab, int i)
{
	t_tokens *node;

	node = malloc(sizeof(t_tokens));
	if(!node)
	{
		free_tab(token_tab);
		node = NULL;
	}
	node->value = token_tab[i];
	if(ft_strncmp(node->value, "|", 1) == 0)
		node->type = PIPE;
	else if(ft_strncmp(node->value, "<", 1) == 0)
		node->type = REDIR_IN;
	else if(ft_strncmp(node->value, ">", 1) == 0)
		node->type = REDIR_OUT;
	else if(ft_strncmp(node->value, "<<", 1) == 0)
		node->type = APP_IN;
	else if(ft_strncmp(node->value, ">>", 1) == 0)
		node->type = APP_OUT;
	else
		node->type = WORD;
	node->next = NULL;
	return (node);
}

t_tokens *lexer(char **token_tab)
{
	int i;
	t_tokens *begin;
	t_tokens *curr;

	begin = get_node(token_tab, 0);
	curr = begin;
	i = 1;
	while(token_tab[i] != NULL)
	{
		curr->next = get_node(token_tab, i);
		curr = curr->next;
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