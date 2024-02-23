#include "../inc/minishell.h"

/*Варианты использования : 

1/ export VARIABLE=value

2/ export

3/export PATH=/usr/local/bin:$PATH

4/export VARIABLE_NAME

5/export VAR1="value1" VAR2="value2"

Постоянная установка переменных среды:
В файле ~/.bash_profile (или ~/.bashrc) вы можете использовать export для установки переменных среды так, чтобы они были доступны при каждом запуске оболочки.*/

int ft_export(t_list_env *list, char *to_key, char *to_value)
{
	int len;

	len = ft_strlen(to_key);
	while(list->next != 0)
	{
		if(ft_strncmp(list->key, to_key, len) == 0)
		{
			//сначала сохранить в tmp
			free(list->value);
			list->value = ft_strdup(to_value);
			break;
		}
		list = list->next;
		if(ft_strncmp(list->key, to_key, len) == 0)
		{
			free(list->value);
			list->value = ft_strdup(to_value);
		}
	}
	printf("%s=%s\n", list->key, list->value);
	return (0);
}