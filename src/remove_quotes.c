#include "../inc/parsing.h"

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
				if(str[i] == '"') //do expand inside
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
