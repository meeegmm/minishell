#include "../../inc/parsing.h"

// int	not_in_path(char *str)
// {
// 	int		i;
// 	char	*tab[6];

// 	i = 0;
// 	tab[0] = "cd";
// 	tab[1] = "env";
// 	tab[2] = "pwd";
// 	tab[3] = "echo";
// 	tab[4] = "unset";
// 	tab[5] = "export";
// 	while (str[i] && i <= 5)
// 	{
// 		if (ft_strncmp(str, tab[i], ft_strlen(tab[i])) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	is_built2(char *str)
// {
// 	int		i;
// 	char	*tab[6];

// 	i = 0;
// 	tab[0] = "env";
// 	tab[1] = "pwd";
// 	tab[2] = "echo";
// 	while (str[i] && i <= 2)
// 	{
// 		if (ft_strncmp(str, tab[i], ft_strlen(tab[i])) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

char	*clean_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] != '/')
		i--;
	i++;
	str = str + i;
	return (str);
}

t_group *parser(char *line, char **envp)
{
	char **token_tab;
	t_tokens *token_list;
	t_group *group;
	
	if(only_spaces(line))
		return(invalid_group(1));
	line = remove_quotes(line);
	if(line == NULL)
		return (invalid_group(1));
	token_tab = ft_split1(line, 1);
	free(line);
	if(token_tab == NULL)
		return (NULL);
	token_list = lexer(token_tab);
	if(!token_list)
	{
		free_tab(token_tab);
		return (NULL);
	}
	group = get_group_list(token_list, envp);
	if (!group)
	{
		free_tab(token_tab);
		free_tokens(token_list);
		return (NULL);
	}
	free_tab(token_tab);
	return (group);
}

// t_group *parser(char *line, char **envp)
// {
// 	char **token_tab;
// 	t_tokens *token_list;
// 	// t_tokens *start; //removed
// 	t_group *group;
	
// 	if(only_spaces(line))
// 		return(invalid_group(1)); //is this number ok?

// 	line = remove_quotes(line);
// 	if(line == NULL)
// 		return (invalid_group(1)); //malloc pb or unclosed quotes

// 	// printf("no quotes + expand: %s\n", line); //do expand

// 	token_tab = ft_split1(line, 1);
// 	free(line); //leak fix
// 	if(token_tab == NULL)
// 		return (NULL); //malloc pb

// 	// to check syntax problems here //
// 		//if(syntax_pb(token_tab) != 0)
// 			// group = invalid_group(); (bash: syntax error near unexpected token `>>')

// 	token_list = lexer(token_tab);
// 	// start = token_list; //removed
// 	if(token_list == NULL)
// 	{
// 		free_tab(token_tab); //leak fix
// 		return (NULL); //malloc pb
// 	}
// 	else
// 	{
// 		// printf("Token list:\n");
// 		// print_token_list(token_list);
// 		// printf("\n");
// 		// token_list = start; //removed
// 		group = get_group_list(token_list, envp);
// 		// print_group(group); //shoudn't work for non-existing cmd
// 	}
// 	free_tab(token_tab); //leak fix
// 	// free_tokens(token_list);
// 	return (group);
// }