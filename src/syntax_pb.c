#include "../inc/parsing.h"

void syntax_pb_msg(char *s)
{
	ft_putstr_err("minishell: syntax error near unexpected token `");
	ft_putstr_err(s);
	ft_putstr_err("'\n");
}

int syntax_pb(t_tokens *list)
{
	if(list->type == 5)
	{
		ft_putstr_err("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while(list != NULL)
	{
		if(list->type >= 1 && list->type <= 4 && list->next != NULL && list->next->type != 0) //to think abt app_in (heredoc)
		{
			syntax_pb_msg(list->value);
			return (1);
		}
		if(list->type != 0 && list->next != NULL && list->next->type == 5)
		{
			syntax_pb_msg(list->value);
			return (1);
		}
		if(list->type != 0 && list->next == NULL)
		{
			ft_putstr_err("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}