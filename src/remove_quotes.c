#include "../inc/parsing.h"

int is_meta(char **str)
{
	if(**str == '|')
	{
		(*str)++;
		return (5);
	}
	else if(**str == '>')
	{
		(*str)++;
		if(**str && **str == '>')
		{
			(*str)++;
			return (4);
		}
		else
			return (2);
	}
	else if(**str == '<')
	{
		(*str)++;
		if(**str && **str == '<')
		{
			(*str)++;
			return (3);
		}
		else
			return (1);
	}
	else
		return (0);
}

char *quotes_ok(char *str) //faire plus court + убедиться, что замена происходит + подумать, что возвращать
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
					str[start] = 29;
					str[i] = 31;
					//
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
					str[start] = 30;
					str[i] = 31;
					break;
				}
			}
		}
		if(str[i])
			i++;
	}
	if(res == 0)
	{
		ft_putstr_err("Invalid syntax: unclosed quotes\n");
		//free(?)
		return (NULL); //подумать, как записать это во flag_fail
	}
	else
	{
		return (str);
	}
}

int new_spaces_nb(char *str)
{
	int counter;
	
	counter = 0;
	while(*str)
	{
		if(is_meta(&str) > 0)
			counter++;
		else
			str++; //как будто тоже можно включить в саму is_meta, но неясно, как изменить тогда
	}
	return (counter * 2);
}

char *remove_quotes(char *str) //+ remove quotes
{
	char *new_str;
	int len;
	int i;
	
	i = 0;
	str = quotes_ok(str);
	if(str == NULL)
		return (NULL);

	len = new_spaces_nb(str) + ft_strlen(str) + 1; 

	new_str = malloc(sizeof(char) * len);
	if(!new_str)
		return (NULL);

	while(i < len && *str)
	{
		if(*str == 29 || *str == 30)
		{
			str++;
			while(*str && *str != 30 && i < len)
			{
				new_str[i] = *str;
				str++;
				i++;
			}
			if(*str)
				str++;
		}
		if(*str && (is_meta(&str) > 0) && (i + 2 < len))
		{
			new_str[i] = ' ';
			new_str[i + 1] = *str;
			new_str[i + 2] = ' ';
			i += 3;
		}
		new_str[i] = *str;
		if(i < len)
			i++;
		if(*str)
			str++;
	}
	new_str[i] = '\0';
	printf("NEW_STRING : %s\n", new_str);
	return (new_str);
}

int quotes_nb(char *str) // количество пар закрытых кавычек (зачем?)
{
	int nb;

	nb = 0;
	while(*str)
	{
		if(*str == 28 || *str == 30)
			nb++;
		str++;
	}
	return (nb);
}