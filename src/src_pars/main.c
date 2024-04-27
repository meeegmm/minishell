// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
// /*   Updated: 2024/04/27 02:24:06 by memarign         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/27 01:53:02 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_exit(char *line)
{
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
	{
		// free(line);
		return (0);
	}
	else
		return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_group *group;
	t_group *start;
	t_list_env *env;
	t_exec	exec; //add

	(void)ac;
	(void)av[0];

	if (*envp == NULL)
		env = env_lst_sos(); //add
	else
		env = get_list(envp);
	init_exec(&exec); //add
	// set_io(&exec);
	line = readline(">$ ");
	while (is_exit(line))
	{
		if(!line || *line == '\0' || only_spaces(line))
		{
			if(line)
				free(line);
			line = readline(">$ ");
			continue ;
		}
		if (line && *line)
			add_history(line);
		group = parser(line, env);
		if(!group)
		{
			exec.status = 1;
			if(line)
				free(line);
			builtin_exit(&exec, group, env);
		}
		start = group;
		minish(&exec, group, env);
		free(line);
		reset_minish(&exec, start);
		line = readline(">$ ");
	}
	free(line);
	builtin_exit(&exec, group, env);
	return (0);
}


// #include "../inc/minishell.h"
// #include "../../inc/parsing.h"

// int	is_exit(char *line)
// {
// 	if(ft_strlen(line) != 4)
// 		return (1);
// 	if (ft_strncmp(line, "exit", 4) == 0)
// 	{
// 		if(line)
// 			free(line);
// 		return (0);
// 	}
// 	else
// 		return (1);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	char	*line;
// 	t_group *group;
// 	t_group *start;
// 	t_list_env *env;

// 	(void)ac;
// 	(void)av[0];

// 	//obtenir t_env_list envp + changer $SHLVL
// 	env = get_list(envp);

// 	line = readline(">$ ");
// 	while (is_exit(line))
// 	{
// 		if(!line || *line == '\0' || only_spaces(line))
// 		{
// 			if(line)
// 				free(line);
// 			// printf("\n");
// 			line = readline(">$ ");
// 			continue ;
// 		}
// 		if (line && *line)
// 			add_history(line);
// 		group = parser(line, env); //group_list is here

// 		if(!group) //malloc pb
// 		{
// 			if(line)
// 				free(line);
// 			free_envp_list(env);
// 			exit(EXIT_FAILURE); //to think abt builtin exit application here
// 		}
		
// 		start = group;
		
// 		while(group != NULL) //on parcours la liste de groupes
// 		{
// 			if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
// 			{
// 				//changer global var en fonction de flag_fail
// 				printf("\nParsed :\n");
// 				print_group(group);
// 				printf("\n");
// 				break; 
// 			}
// 			else if(group->flag_fail == 0)
// 			{
// 				//exec magic
// 				//changer global var en fonction de flag_fail
// 			}
// 			printf("\nParsed :\n");
// 			print_group(group);
// 			printf("\n");
// 			group = group->next;
// 		}
// 		free_group_list(start);
// 		free(line);
// 		line = readline(">$ ");
// 	}
// 	free_envp_list(env);
// 	clear_history(); //??
// 	return (0);
// }