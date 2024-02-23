#include "../inc/minishell.h"

int	is_exit(const char *line)
{
	const char	*exit;

	exit = "exit";
	if (*line == *exit)
		return (0);
	else
		return (1);
// pareil pour CTRL + D?
}