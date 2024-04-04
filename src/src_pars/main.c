#include "../../inc/minishell.h"
#include "../../inc/parsing.h"
#include "../../inc/exec.h"

int	is_exit(char *line)
{
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
	{
		free(line);
		return (0);
	}
	else
		return (1);
}

// void	minish(t_exec *exec, t_group *group, t_list_env *env_lst)
// {
	//add checks
// 	while (group->flag_fail == 0)
// 	{
// 		ft_exec(&exec, group, env_lst);
// 		reset_std(&exec);
// 		close_fds(&exec);
// 		init_exec(&exec);
// 	}
	//get signal
// }

//should not exit when \n
int	main(int ac, char **av, char **envp)
{
	char		**new_envp;
	t_list_env	*env_lst;
	char		*line;
	t_group 	*group;
	// t_group 	*start;
	t_exec		exec;

	(void)ac;
	(void)av[0];
	//obtenir t_env_list envp + changer $SHLVL
	new_envp = set_envp(envp);
	env_lst = get_list(new_envp);
	init_exec(&exec);
	init_std(&exec);
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		group = parser(line, envp); //group_list is here
		if(!group) //malloc pb
		{
			if(line)
				free(line);
			exit(EXIT_FAILURE); //to think abt builtin exit application here
		}
		// start = group;
		//supposed to be in while
		if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
		{
			//changer global var en fonction de flag_fail
			line = NULL;
			break;
		}
		else
		{
		// 	while(group != NULL) //on parcours la liste de groupes
		// 	{
			ft_exec(&exec, group, env_lst);
			reset_std(&exec);
			close_fds(&exec);
			init_exec(&exec);
			// waitpid(-1, NULL, 0);
			line = NULL;
				//changer global var en fonction de flag_fail
		}
		// group = group->next;
		free_group_list(group); //FREE
		line = readline(">$ ");
		// if(line)
		// 	free(line); //do we really need it? (recheck with no other leaks)
	}
	return (0);
}

