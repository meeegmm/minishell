/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:09:08 by memarign          #+#    #+#             */
/*   Updated: 2024/02/17 05:32:06 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	is_exit(const char *line)
{
	const char	*exit;

	exit = "exit";
	if (*line == *exit)
		return (0);
	else
		return (1);
//pareil pour CTRL + D?
}

int	main(void)
{
	const char	*line;

	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		printf("%s\n", line);
		// free(line);
		line = readline(">$ ");
	}
}
