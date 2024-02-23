#include "../inc/minishell.h"

/*
unset VARIABLE_NAME

unset VARIABLE_NAME1 VARIABLE_NAME2 ...

unset -- VARIABLE_NAME (если имя переменной начинается с дефиса -)
*/

int ft_unset(t_list_env *list)
{
	while(list != NULL)
	{
		if(ft_strncmp(list->key, lg->cmd[1], ft_strlen(lg->cmd[1]) == 0))
		{
			///
			break;
		}
		list = list->next;
	}
}