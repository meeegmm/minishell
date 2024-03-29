#include "../inc/parsing.h"
#include "../inc/minishell.h"

char *no_null()
{
	char *str;
	str = malloc(sizeof(char) * 2);
	if(!str)
		return (NULL);
	str[0] = 28;
	return (str);
}

int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
    return (c >= '1' && c <= '9');
}

int is_special(char c)
{
	return (!is_digit(c) && !is_alpha(c) && c != '*' && c != '#' && c != '?' && c != ' ' && c != '\t');
}

int delimiter_nb(char *str)
{
	int nb;
	int i;

	nb = 0;
	i = 0;

	while(str[i])
	{
		if(str[i] == '$' || is_special(str[i]) || str[i] == 30)
			nb++;
		if(str[i] == '$' && str[i + 1] && is_digit(str[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

char *temp_tokenizer(char *str)
{
	int len;
	int i;
	int k;
	char *new;

	i = 0;
	k = 0;
	len = delimiter_nb(str) + ft_strlen(str) + 1;
	new = malloc(sizeof(char) * len);
	if(!new)
		return (NULL);
	while(k < len && str[i])
	{
		if((str[i] == '$' || is_special(str[i]) || str[i] == 30) && (k + 1 < len))
		{
			new[k] = 28;
			new[k + 1] = str[i];
			k += 2;
			i++;
		}
		if(str[i] == '$' && str[i + 1] && is_digit(str[i + 1]) && (k + 2 < len)) //решить проблему с тем, что пробел не сохраняется тут
		{
			new[k] = 28;
			new[k + 1] = '$';
			new[k + 2] = str[i + 1]; 
			k += 3;
			i += 2;
		}
		if(str[i] == 30 && k + 1 < len)
		{
			new[k] = 28;
			new[k + 1] = str[i];
			i++;
			k += 2;
		}
		else
		{
			new[k] = str[i];
			k++;
			i++;
		}
	}
	new[k] = '\0';
	// free(str);
	return (new);
}

char *expanded_token(char *str, t_list_env *env) 
{
	char *res;
	
	res = NULL;

	while(env != NULL)
	{
		if(ft_strncmp(env->key, str, ft_strlen(str)) == 0)
		{
			res = ft_strdup(env->value);
			break;
		}
		else
			env = env->next;
	}
	// free(str);
	return (res);
}

char *replace_token(char *str, t_list_env *env)
{
	int i;
	char *new;

	i = 0;
	if(str[i] != '$')
		new = ft_strdup(str);
	else if(str[i] == '$' && (str[i + 1] == '\0' || (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t'))))
		new = ft_strdup(str);
	else
	{
		if(str[i + 1] && is_digit(str[i + 1]))
		{
			new = no_null();
		}
		else if(str[i + 1] && is_alpha(str[i + 1]))
		{
			str++;
			new = expanded_token(str, env);
			str--;
		}
		//else if(str[i + 1] && str[i + 1] == '?')
			//int status
		else
		{
			new = no_null(); //???
		}
	}
	// free(str);
	return (new);
}

char *from_tab_to_line(char **tab)
{
	int i;
	char *res;
	char *temp;
	
	temp = no_null();
	res = ft_strdup(tab[0]);
	i = 1;
	while(tab[i])
	{
		if(ft_strncmp(tab[i], temp, ft_strlen(tab[i]) != 0))
			res = ft_strjoin(res, tab[i]);
		i++;
	}
	free(temp);
	return (res);
}
	
char *ft_expand(char *str, t_list_env *env)
{
	char *temp;
	char **token_tab;
	int i;
	char **copy; //copy of token_tab

	temp = temp_tokenizer(str);
	if(!temp)
		return (NULL);
	token_tab = ft_split1(temp, 3);
	if(!token_tab)
		return (NULL);

	printf("before-expand tokens :\n");
	print_tab(token_tab);
	
	copy = copy_tab (token_tab);

	// printf("copy tab :\n");
	// print_tab(copy);
	i = 0;
	while(copy[i] && token_tab[i]) 
	{
		copy[i] = NULL;
		copy[i] = replace_token(token_tab[i], env);
		i++;
	}
	printf("after-expand tokens :\n");
	print_tab(copy);
	temp = NULL;
	temp = from_tab_to_line(copy);
	return(temp);
}