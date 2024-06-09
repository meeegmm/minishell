/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madmeg <madmeg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/09 12:13:09 by madmeg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	init_readline(char *line)
// {
// 	if (line)
// 		free(line);
// 	line = readline(">$ ");
// }

// void	exit_group(t_list_env *env, char *line)
// {
// 	if (line)
// 		free(line);
// 	free_envp_list(env);
// 	exit(EXIT_FAILURE);
// }

// void	end_minish(t_exec *exec, t_list_env *env)
// {
// 	free_envp_list(env);
// 	clear_history();
// 	close_fds(&exec);
// }

//Un seul readline, le placer dans la boucle
//Tout exec puis y revenir
//if (!line) do CTRL + D

unsigned int	status;

int	is_exit(char *line)
{
	if(ft_strlen(line) != 4)
		return (1);
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		if(line)
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
	t_list_env	*env;
	t_cmd		command;
	t_exec		exec;
	t_group		*start;

	(void)ac;
	(void)av[0];
	if (*envp == NULL)
		env = env_lst_sos();
	else
	{
		//obtenir t_env_list envp + changer $SHLVL
		env = get_list(envp);
	}
	init_exec(&exec);
	line = readline(">$ "); //signals handled already
	while (is_exit(line))
	{
		if (!line || *line == '\0' || only_spaces(line) || ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0)
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
			status = 1; //??
			if (line)
				free(line);
			free_envp_list(env);
			exit(EXIT_FAILURE);
		}
		start = group;
		minish(&exec, group, &env, &command);
		free_group_list(start);
		reset_minish(&exec);
		if (line)
			free(line);
		line = readline(">$ ");
	}
	free_envp_list(env);
	clear_history();
	close_fds(&exec);
	return (status);
}
//while(1)
//{
//	line = readline
//	if (!line)
//		break; (= CTRL + D)
//	if (globale ndiaue pas de signal)
//	{
//		struct parrsing = parsing
//		if (parsing)
//		{
//			expand 
//			exec
//		}
//	}
//	tout free
//}