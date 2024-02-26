#include "../inc/parsing.h"

//do a list of tokens

t_tokens *lexer(char *str)
{
	char **token_tab;
	int i;
	t_tokens *begin;
	t_tokens *curr;
	
	token_tab = ft_split1(str, 1);
	if(token_tab == NULL)
	{
		perror("tokens");
		return (NULL);
	}

	begin = malloc(sizeof(t_tokens));
	if (begin == NULL)
		return (NULL);
	begin->type = WORD;
	begin->value = token_tab[0];
	begin->next = NULL;
	curr = begin;
	i = 1;
	while(token_tab[i])
	{
		curr->next = malloc(sizeof(t_list_env));
		if(!curr->next)
		{
			//free_token_list(begin);
			return (NULL);
		}
		curr = curr->next;
		curr->type = WORD;
		curr->value = token_tab[i];
		i++;
	}
	curr->next = NULL;
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

t_group *parser(char *line, char **envp) //или эта функция, или get_group избыточная
{
	t_tokens *list;
	t_group *group;

	list = lexer(line);
	if(list == NULL)
	{
		printf("Problem");
		exit(EXIT_FAILURE);
	}
	// printf("list->type %d\n", list->type);
	// printf("list->len %d\n", list->len);
	// printf("list->value %s\n", list->value);

	group = get_group(list, envp);
	if(group->flag_fail == 1)
	{
		free_tokens(list);
		printf("invalid cmd");
		exit(EXIT_FAILURE);
	}
	return (group);
}