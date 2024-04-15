#include "../../inc/minishell.h"
#include "../../inc/parsing.h"
#include "../../inc/exec.h"

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

// void	minish(t_exec *exec, t_group *group, t_list_env *env_lst)
// {
// 	// add checks
// 	// while (group->flag_fail == 0)
// 	// {
// 		// ft_exec(exec, group, env_lst);
// 		reset_std(exec);
// 		close_fds(exec);
// 		init_exec(exec);
// 	// }
// 	// get signal
// }

int	main(int ac, char **av, char **envp)
{
	char		**new_envp;
	t_list_env	*env_lst;
	char		*line;
	t_group 	*group;
	t_group		*start;
	t_exec		exec;

	(void)ac;
	(void)av[0];
	new_envp = set_envp(envp);
	env_lst = get_list(new_envp);
	init_std(&exec);
	init_exec(&exec);
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		// else
		// {
		// 	free(line);
		// 	free_tab(new_envp);
		// 	free_envp_list(env_lst);
		// 	return (2);
		// }
		group = parser(line, new_envp);
		if(!group)
		{
			free(line);
			free_tab(new_envp);
			free_envp_list(env_lst);
			return (3);
		}
		// else
		start = group;
		while (group != NULL)
		{
			if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL))
			{
				break ;
				// free_envp_list(env_lst);
				// free_tab(new_envp);
				// free_group_list(group);
				// line = NULL;
				// exit(EXIT_FAILURE);
			}
			else if (group->flag_fail == 0)
			{
				ft_exec(&exec, group);
				if (group->next != NULL)
					ft_pipe(&exec);
				simple_cmd(&exec, group, env_lst);
			}
			group = group->next;
		}
		line = NULL;
		reset_std(&exec);
		close_fds(&exec);
		init_exec(&exec);
		free_group_list(start);
		line = readline(">$ ");
	}
	free_envp_list(env_lst);
	free_tab(new_envp);
	builtin_exit(&exec, group);
	return (0);
}


//should not exit when \n
//add print group
// int	main(int ac, char **av, char **envp)
// {
// 	char		**new_envp;
// 	t_list_env	*env_lst;
// 	char		*line;
// 	t_group 	*group;
// 	// t_group 	*start;
// 	t_exec		exec;

// 	(void)ac;
// 	(void)av[0];
// 	//obtenir t_env_list envp + changer $SHLVL
// 	new_envp = set_envp(envp);
// 	env_lst = get_list(new_envp);
// 	init_exec(&exec);
// 	init_std(&exec);
// 	line = readline(">$ ");
// 	while (is_exit(line))
// 	{
// 		if (line && *line)
// 			add_history(line);
// 		else //to be replaced by builtin_exit()
// 		{
// 			free(line);
// 			free_tab(new_envp);
// 			free_envp_list(env_lst);
// 			free_group_list(group);
// 			exit(EXIT_FAILURE);
// 		}
// 		group = parser(line, new_envp); //group_list is here
// 		if(!group) //malloc pb
// 		{
// 			if(line)
// 				free(line);
// 			free_envp_list(env_lst);
// 			free_tab(new_envp);
// 			exit(EXIT_FAILURE); //to think abt builtin exit application here
// 		}
// 		// start = group;
// 		//supposed to be in while
// 		if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
// 		{
// 			//changer global var en fonction de flag_fail
// 			free_group_list(group); // add other FREE
// 			line = NULL;
// 			// break;
// 		}
// 		else
// 		{
// 		// 	while(group != NULL) //on parcours la liste de groupes
// 		// 	{
// 			ft_exec(&exec, group, env_lst);
// 			reset_std(&exec);
// 			close_fds(&exec);
// 			init_exec(&exec);
// 			free_group_list(group); // add other FREE
// 			// waitpid(-1, NULL, 0);
// 			line = NULL;
// 				//changer global var en fonction de flag_fail
// 		}
// 		// group = group->next;
// 		line = readline(">$ ");
// 		// if(line)
// 		// 	free(line); //do we really need it? (recheck with no other leaks)
// 	}
// 	free_envp_list(env_lst);
// 	free_tab(new_envp);
// 	return (0);
// }

