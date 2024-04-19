#include "../../inc/exec.h"

void	minish(t_exec *exec, t_group *group, t_list_env *env)
{
	while(group != NULL) //on parcours la liste de groupes
	{
		if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
		{
			//changer global var en fonction de flag_fail
			//exit
			break; 
		}
		else if(group->flag_fail == 0)
		{
			ft_redir(exec, group);
			if (group->next != NULL)
				ft_pipe(exec);
			simple_cmd(exec, group, env);
			// printf("exec->status: %d\n", exec->status);
			
			//exec magic
			//changer global var en fonction de flag_fail
		}
		group = group->next;
	}
}

void	reset_minish(t_exec *exec, t_group *start)
{
		free_group_list(start);
		close_fds(exec); //add
		reset_std(exec); //add
		close_std(exec); //add
		init_exec(exec); //add
}