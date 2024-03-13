#include "../../inc/parsing.h"

int not_in_path(char *str)
{
	int i;
	char *tab[2];

	i = 0;
	tab[0] = "unset";
    tab[1] = "export";
	while (str[i] && i <= 1)
    {
        if (ft_strncmp(str, tab[i], ft_strlen(tab[i])) == 0)
            return (1);
        i++;
    }
    return (0);
}

int    is_built2(char *str)
{
    int        i;
    char    *tab[6];

    i = 0;
    tab[0] = "cd";
    tab[1] = "env";
    tab[2] = "pwd";
    tab[3] = "echo";
    while (str[i] && i <= 3)
    {
        if (ft_strncmp(str, tab[i], ft_strlen(tab[i])) == 0)
            return (1);
        i++;
    }
    return (0);
}

char *clean_cmd(char *str) //добавить проверку, что переданный path absolut существует
{
	int i;

	i = 0;
	while(str[i])
		i++;
	i--;
	while(str[i] != '/')
		i--;
	i++;
	str = str + i;
	return (str);
}

//quotes check

/*void condition_part(int *res, char *str, char c)
{
	*res = 0;
	while(*str)
	{
		str++;
		if(*str == c)
		{
			*res = 1;
			break;
		}
	}
}

int quotes_ok(char *str)
{
	int res;

	res = 1;
	while(*str)
	{

		if(*str == '"')
		{
			condition_part(&res, str, '"');
		}
		else if(*str == 39)
		{
			condition_part(&res, str, 39);
		}
		str++;
	}
	return (res);
}*/


int is_meta(char c) //gere tout sauf >> <<
{
	return(c == '>' || c == '<' || c == '|');
}


char *quotes_ok(char *str) //faire plus court
{
	int i;
	int res;
	int start;

	i = 0;
	res = 1;
	while(str[i])
	{
		if(str[i] == '"')
		{
			res = 0;
			start = i;
			while(str[i])
			{
				i++;
				if(str[i] == '"')
				{
					res = 1;
					str[start] = 31;
					str[i] = 30;
					break;
				}

			}
		}
		else if(str[i] == '\'')
		{
			res = 0;
			start = i;
			while(str[i])
			{
				i++;
				if(str[i] == '\'')
				{
					res = 1;
					str[start] = 31;
					str[i] = 30;
					break;
				}
			}
		}
		i++;
	}
	if(res == 0)
	{
		printf("Invalid syntax: quotes\n");
		free(str);
		return (NULL);
	}
	else
		return (str);
}

int new_spaces_nb(char *str)
{
	int nb;

	nb = 0;
	while(*str)
	{
		if(*str == 31)
		{
			while(*str != 30)
				str++;
			str++;
		}
		if(is_meta(*str) == 1)
			nb++;
		str++;
	}
	return (nb * 2);
}

char *spaces_before_meta(char *str) //+ remove quotes
{
	char *new_str;
	int len;
	int i;
	int k;
	
	i = 0;
	k = 0;
	str = quotes_ok(str);
	if(str == NULL)
		return (NULL);
	len = new_spaces_nb(str) + ft_strlen(str) + 1;

	new_str = malloc(sizeof(char) * len);
	if(!new_str)
		return (NULL);
	while(i < len && str[k])
	{
		if(str[k] == 31)
		{
			new_str[i] = ' ';
			i++;
			k++;
			while(str[k] != 30)
			{
				new_str[i] = str[k];
				k++;
				i++;
			}
			new_str[i] = ' ';
			i++;
			k++;
		}
		if(is_meta(str[k]) == 1 && (i + 2 < len))
		{
			new_str[i] = ' ';
			new_str[i + 1] = str[k];
			new_str[i + 2] = ' ';
			i += 3;
			k++;
		}
		new_str[i] = str[k];
		i++;
		k++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int quotes_nb(char *str)
{
	int nb;

	nb = 0;
	while(*str)
	{
		if(*str == 31)
			nb++;
		str++;
	}
	return (nb);
}

char *remove_quotes(char *str)
{
	str = spaces_before_meta(str);
	if(str == NULL)
		return (NULL);
	return (str);
}

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

t_group *invalid_group(void)
{
	t_group *group;
	group = malloc(sizeof(t_group));
	if(!group || group == NULL)
	{
		perror("group malloc");
		return (NULL);
	}
	group->cmd = NULL;
	group->next = NULL;
	group->flag_fail = 1;
	return (group);
}

t_group *get_group(t_tokens *list, char **envp)
{
	t_group *group;
	group = malloc(sizeof(t_group));
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
	if(not_in_path(group->cmd[0]))
		group->flag_fail = 0;
	else
	{
		group->cmd[0] = cmd_check(group->cmd, envp); //детальнее разобраться, когда NULL
		if(group->cmd[0] == NULL)
		{
			free(group);
			perror("Error");
			return (invalid_group());
		}
		else
		{
			char *copy = ft_strdup(group->cmd[0]);
			if(is_built2(clean_cmd(copy))) //&& group->cmd[0][0] == '/')
				group->cmd[0] = clean_cmd(group->cmd[0]);
			group->flag_fail = 0;
			free(copy);
		}
	}
	return (group);
}

t_group *parser(char *line, char **envp) //или эта функция, или get_group избыточная
{
	t_tokens *list;
	t_group *group;
	char **token_tab;
	
	line = remove_quotes(line);
	if(line == NULL)
	{
		return (invalid_group()); //make more explicite
	}
	//printf("new line : %s\n", line);

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
		return (NULL);
	}
	
	//if(syntax_pb(line) != 0)
	// 	group = invalid_group();
	else
	{
		group = get_group(list, envp); //shoudn't work for non-existing cmd
		//free_tokens(list);
	}
	return (group);
}