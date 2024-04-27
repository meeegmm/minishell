#include "../../inc/exec.h"

void	minish(t_exec *exec, t_group *group, t_list_env *env)
{
	while(group != NULL) //on parcours la liste de groupes
	{
		if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
		{
			reset_minish(exec, group);
			break; 
		}
		else if(group->flag_fail == 0)
		{
			// ft_redir(exec, group);
			if (group->next != NULL)
				ft_pipe(exec);
			simple_cmd(exec, group, env);
		}
		if (exec->status == 0)
			group = group->next;
		else
			builtin_exit(exec, group, env);
	}
}

void	reset_minish(t_exec *exec, t_group *start)
{
	if (start != NULL)
		free_group_list(start);
	close_fds(exec); //add
	// close_std(exec);
	init_exec(exec); //add
	set_io(exec); //add
}