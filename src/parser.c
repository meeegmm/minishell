#include "../inc/parsing.h"

//do a list of tokens

int is_separator(char c)
{
	return (c == ' ' || c == '\t');
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

#include "../inc/minishell.h"

int	is_exit(const char *line)
{
	const char	*exit;

	exit = "exit";
	if (*line == *exit)
		return (0);
	else
		return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av[0];
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		t_tokens *list = lexer(line);
		if(list == NULL)
		{
			printf("Problem");
			exit(EXIT_FAILURE);
		}
		// printf("list->type %d\n", list->type);
		// printf("list->len %d\n", list->len);
		// printf("list->value %s\n", list->value);
		t_group *group = get_group(list, envp);
		if(group->flag_fail == 1)
		{
			free_tokens(list);
			printf("invalid cmd");
			exit(EXIT_FAILURE);
		}
		else
			print_tab(group->cmd);
		line = NULL;
		line = readline(">$ ");
	}
}