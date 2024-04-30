/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/30 13:17:10 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_exit(char *line)
{
	if (ft_strlen(line) != 4)
		return (1);
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		if (line)
			free(line);
		return (0);
	}
	else
		return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_group		*group;
	t_group		*start;
	t_list_env	*env;
	t_exec		exec;

	(void)ac;
	(void)av[0];

	if (*envp == NULL)
		env = env_lst_sos();
	else
		env = get_list(envp);
	init_exec(&exec);
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (!line || *line == '\0' || only_spaces(line))
		{
			if (line)
				free(line);
			line = readline(">$ ");
			continue ;
		}
		if (line && *line)
			add_history(line);
		group = parser(line, env);
		if (!group)
		{
			exec.status = 1;
			if (line)
				free(line);
			builtin_exit(&exec, group, env);
		}
		start = group;
		minish(&exec, group, env);
		free(line);
		reset_minish(&exec, start);
		line = readline(">$ ");
	}
	if (line)
		free(line);
	builtin_exit(&exec, group, env);
	// return (0);
}
