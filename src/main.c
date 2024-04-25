/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/25 15:59:09 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

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
	char	*line;
	t_group *group;
	t_group *start;
	t_list_env *env;

	(void)ac;
	(void)av[0];

	//obtenir t_env_list envp + changer $SHLVL
	env = get_list(envp);

	line = readline(">$ ");
	while (is_exit(line))
	{
		if(!line || *line == '\0' || only_spaces(line) || ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0) // TO FIX "" and ''
		{
			if(line)
				free(line);
			// printf("\n");
			line = readline(">$ ");
			continue ;
		}
		if (line && *line)
			add_history(line);
		group = parser(line, env); //group_list is here

		if(!group) //malloc pb
		{
			if(line)
				free(line);
			free_envp_list(env);
			exit(EXIT_FAILURE); //to think abt builtin exit application here
		}
		
		start = group;
		
		while(group != NULL) //on parcours la liste de groupes
		{
			if(group->flag_fail == 2 /*|| (group->flag_fail == 127 && group->next == NULL)*/) //if syntax pb or the last cmd is not found
			{
				//changer global var en fonction de flag_fail
				// printf("\nParsed :\n");
				// print_group(group);
				// printf("\n");
				break; 
			}
			else if(group->flag_fail == 0)
			{
				//exec magic
				//changer global var en fonction de flag_fail
			}
			printf("\nParsed :\n");
			print_group(group);
			printf("\n");
			group = group->next;
		}
		free_group_list(start);
		if(line)
			free(line);
		line = readline(">$ ");
	}
	free_envp_list(env);
	clear_history(); //??
	return (0);
}