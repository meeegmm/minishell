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

///////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *s)
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	return (i);
}

void free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strdup(char *s1)
{
	char	*s;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s = (char*)malloc(sizeof(*s1) * (len + 1));
	if (s == NULL)
		return (NULL);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
	printf("\n");
}

char **file_access(char **tab)
{
    int i;

    i = 0;
    char **res = malloc(sizeof(char *) * 2);
    if(!res)
        return(NULL); 
    while(tab[i])
    {
        if(access(tab[i], F_OK | R_OK | W_OK ) != 0) //should we remove X_OK ?
        {
            free(res);
            return (NULL);
        }
        i++;
    }
    res[0] = ft_strdup(tab[i - 1]);
    res[1] = NULL;
    return (res);
}

int main()
{
    char **tab = malloc(sizeof(char *) * 4);
    tab[0] = "file1";
    tab[1] = "file2";
    tab[2] = "file3";
    tab[3] = NULL;

    char **res = file_access(tab);
    if(res != NULL)
    {
        printf("le vrai output : %s\n", res[0]);
        free_tab(res);
    }
    else
        printf("No access\n");
    free(tab);
    return (0);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	res = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}

// void	free_tab1(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i] != NULL)
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// }

// void	free_tab(char **tab)
// {
// 	free_tab1(tab);
// 	free(tab);
// }


// printf("Token list:\n");
// 	print_token_list(p->token_list);
// 	printf("\n");


char	**copy_tab(char **tab)
{
	int		nb_line;
	int		i;
	char	**copy;

	nb_line = 0;
	i = 0;
	while (tab[nb_line])
		nb_line++;
	copy = malloc(sizeof(char **) * (nb_line));
	while (i < nb_line && tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// t_group *parser(char *input, t_list_env *env)
// {
// 	t_parser *p;
// 	t_group *group;

// 	p = create_init_p();
// 	group = create_init_group();
// 	p->line = quotes_expand(input, env);
// 	if(p->line == NULL)
// 	{
// 		free_t_parser(p);
// 		if(input)
// 		{
// 			invalid_group(group, 127);
// 			ft_putstr_err("Command not found\n");
// 		}
// 		else
// 			invalid_group(group, 2); //NOT SURE ABOUT 2 (should be 0?)
// 		return (group);
// 	}
// 	p->token_tab = ft_split1(p->line, 1);
// 	if(p->token_tab == NULL)
// 	{
// 		free_t_parser(p);
// 		return (NULL);
// 	}
// 	spaces_between_quotes(&(p->token_tab));
// 	p->token_list = lexer(p->token_tab);
// 	if(p->token_list == NULL)
// 	{
// 		free_t_parser(p);
// 		return (NULL);
// 	}
// 	if(syntax_pb(p->token_list))
// 	{
// 		free_t_parser(p);
// 		invalid_group(group, 2);
// 		return (group);
// 	}
// 	else
// 	{
// 		free(group);
// 		group = get_group_list(p->token_list, env);
// 	}
// 	free_t_parser(p);
// 	return (group);
// }