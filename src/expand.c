#include "../inc/parsing.h"
#include "../inc/minishell.h"

char *no_NULL()
{
	char *str;
	str = malloc(sizeof(char) * 2);
	if(!str)
		return (NULL);
	str[0] = 31;
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
		if(str[i] == '$' || is_special(str[i]))
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
		if((str[i] == '$' || is_special(str[i])) && (k + 1 < len))
		{
			new[k] = 30;
			new[k + 1] = '$';
			k += 2;
			i++;
		}
		if(is_digit(str[i]) && str[i - 1] && str[i - 1] == '$' && (k + 1 < len)) //решить проблему с тем, что пробел не сохраняется тут
		{
			new[k] = str[i];
			new[k + 1] = 30;
			k += 2;
			i++;
		}
		if(k < len && str[i])
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
			new = ft_strdup("XX");
		}
		else if(str[i + 1] && is_alpha(str[i + 1]))
		{
			str++;
			new = expanded_token(str, env);
		}
		//else if(str[i + 1] && str[i + 1] == '?')
			//int status
		else
		{
			new = ft_strdup("XX");
		}
	}
	// free(str);
	return (new);
}
	
char *ft_expand(char *str, char **envp)
{
	char *temp;
	char **token_tab;
	t_list_env *env; //переписать все так, чтобы в параметрах везде был list
	int i;

	i = 0;
	temp = temp_tokenizer(str);
	if(!temp)
		return (NULL);
	token_tab = ft_split1(temp, 3);
	if(!token_tab)
		return (NULL);
	
	env = get_list(envp);
	while(token_tab[i]) //походу надо создавать новую таблицу
	{
		free(temp);
		temp = replace_token(token_tab[i], env);
		free(token_tab[i]);
		token_tab[i] = ft_strdup(temp);
		i++;
	}
	print_tab(token_tab);
	return(token_tab[i]);
}