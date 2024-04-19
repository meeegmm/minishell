/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/19 04:33:10 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// #include "../../inc/parsing.h"
// #include "../../inc/exec.h"

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

// void	minish(t_exec *exec, t_group *group, t_list_env *env)
// {
// 	while(group != NULL) //on parcours la liste de groupes
// 	{
// 		if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
// 		{
// 			//changer global var en fonction de flag_fail
// 			//exit
// 			break; 
// 		}
// 		else if(group->flag_fail == 0)
// 		{
// 			ft_redir(exec, group);
// 			if (group->next != NULL)
// 				ft_pipe(exec);
// 			simple_cmd(exec, group, env);
// 			printf("exec->status: %d\n", exec->status);
			
// 			//exec magic
// 			//changer global var en fonction de flag_fail
// 		}
// 		group = group->next;
// 	}
// }

// void	reset_minish(t_exec *exec, t_group *start)
// {
// 		free_group_list(start);
// 		close_fds(exec); //add
// 		reset_std(exec); //add
// 		init_exec(exec); //add
// 		close_std(exec); //add
// }

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_group *group;
	t_group *start;
	t_list_env *env;
	t_exec	exec; //add

	(void)ac;
	(void)av[0];

	//obtenir t_env_list envp + changer $SHLVL
	//check envp == NULL
	if (*envp == NULL)
		env = env_lst_sos(); //add
	else
		env = get_list(envp);
	init_exec(&exec); //add
	// init_std(&exec);

	line = readline(">$ ");
	while (1)
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
		init_std(&exec);
		group = parser(line, env);
		if(!group)
		{
			if(line)
				free(line);
			free_envp_list(env);
			close_std(&exec);
			exit(EXIT_FAILURE); //to think abt builtin exit application here
		}
		
		start = group;
		minish(&exec, group, env);
		free(line);
		reset_minish(&exec, start);
		line = readline(">$ ");
	}
	end_minish(&exec, start, env);
	return (0);
}