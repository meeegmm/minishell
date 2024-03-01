#include "../../inc/parsing.h"

//quotes check

int quotes_ok(char *str) //faire plus court
{
	int i;
	int res;

	i = 0;
	res = 1;
	while(str[i])
	{
		if(str[i] == '"')
		{
			res = 0;
			while(str[i])
			{
				i++;
				if(str[i] == '"')
				{
					res = 1;
					break;
				}
			}
		}
		else if(str[i] == 39)
		{
			res = 0;
			while(str[i])
			{
				i++;
				if(str[i] == 39)
				{
					res = 1;
					break;
				}
			}
		}
		i++;
	}
	return (res);
}

//realloc - enlever les quotes

//do a list of tokens

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
		curr->type = WORD;
		curr->value = token_tab[i];
		curr->next = NULL;
		i++;
	}
	return (begin);
}

t_group *get_group(t_tokens *list, char **envp)
{
	t_group *group;
	group = malloc(sizeof(group));
	if(!group)
	{
		perror("group malloc");
		return (NULL);
	}
	group->cmd = get_tab(list);
	if(!group->cmd)
	{
		perror("malloc problem");
		return (NULL);
	}
	group->cmd[0] = cmd_check(group->cmd, envp); //детальнее разобраться, когда NULL
	if(group->cmd == NULL)
		group->flag_fail = 1; //так ли нужен flag_fail ?
	else
		group->flag_fail = 0;
	return (group);
}

int syntax_pb(char *line)
{
	if(quotes_ok(line) != 1)
	{
		printf("Invalid input: quotes\n");
		return (1);	
	}
	///////// plenty of other cases ////////
	return (0);
}

t_group *invalid_group(void)
{
	t_group *group;
	group = malloc(sizeof(group));
	if(!group)
	{
		perror("group malloc");
		return (NULL);
	}
	group->cmd = NULL;
	group->next = NULL;
	group->flag_fail = 1;
	return (group);
}

t_group *parser(char *line, char **envp) //или эта функция, или get_group избыточная
{
	t_tokens *list;
	t_group *group;
	char **token_tab;

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
	{
		perror("tokens");
		return (NULL);
	}
	list = lexer(token_tab);
	if(list == NULL)
	{
		printf("Problem");
		exit(EXIT_FAILURE);
	}
	// printf("list->type %d\n", list->type);
	// printf("list->len %d\n", list->len);
	// printf("list->value %s\n", list->value);
	
	if(syntax_pb(line) != 0)
		group = invalid_group();
	else
	{
		group = get_group(list, envp); //shoudn't work for non-existing cmd
		free_tokens(list);
	}
	return (group);
}