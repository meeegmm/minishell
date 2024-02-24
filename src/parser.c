#include "../inc/parsing.h"

//do a list of tokens

int is_separator(char c)
{
	return (c == ' ' || c == '\t'); //точно ли так использовать \t?
}

t_tokens *lexer(char *str)
{
	t_tokens *begin;
	int i;
	int start;

	i = 0;
	start = 0;
	begin = malloc(sizeof(t_tokens));
	if (begin == NULL)
		return (NULL);
	
	while(str[i] && is_separator(str[i]) == 1)
		i++;
	if(is_separator(str[i]) == 0)
		start = i;
	while(str[i] && is_separator(str[i]) == 0)
		i++;
	begin->len = i - start;
	begin->type = WORD;
	begin->value = malloc(sizeof(char) * (begin->len + 1));
	start = begin->len;
	begin->value[begin->len + 1] = '\0';
	while(start >= 0)
	{
		begin->value[start] = str[i];
		start--;
		i--;
	}
	i += begin->len;
	begin->next = NULL;
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

int main(int ac, char **av, char **envp)
{
	if(ac != 2)
		exit(EXIT_FAILURE);
	
	t_tokens *list = lexer(av[1]);
	if(list == NULL)
	{
		perror("malloc list");
		exit(EXIT_FAILURE);
	}

	// printf("list->type %d\n", list->type);
	// printf("list->len %d\n", list->len);
	// printf("list->value %s\n", list->value);

	t_group *group = get_group(list, envp);
	if(group->flag_fail == 1)
	{
		free_tokens(list);
		perror("invalid cmd");
		exit(EXIT_FAILURE);
	}
	else
	{
		print_tab(group->cmd);
	}
	return (0);
}