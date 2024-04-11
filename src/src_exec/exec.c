#include "../../inc/minishell.h"
#include "../../inc/exec.h"

//exec last cmd exec first: check recursive function
//check fd open when |
//add fd in putstr?
//>$ bin > a | other cmd: out = a
//>$ builtin | bin > a = builtin write in redir (should only do 2nd)
//>$ builtin > a | bin > b: builtin in a and bin in b
//>$ echo a > b | ls > c: result in c (should do both)
//>$ echo a > b | ls > c: b created but empty (when if !group->next)
//>$ bin > a | echo b = b write in a (shoul do both command)
//>$ builtin | builtin: next cmd builtin  = not found 
//>$ builtin > a = okay
//>$ cat a = a>$

//add printf
//add checks
void	ft_bin(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	char	**envp;
	pid_t	pid;

	envp = get_envp(env_lst);
	if (group->flag_fail)
	{
		ft_putstr_fd("minishell", "error", 2);
		write(2, "Command not found\n", 18);
		return ;
	}
	if (exec->pid == -1)
	{
		pid = fork();
		exec->pid = pid;
	}
	if (exec->pid == 0)
	{
		if (execve(group->cmd[0], group->cmd, envp) == 0)
		{
			if (access(group->cmd[0], F_OK | X_OK) == -1)
			{
				ft_putstr_fd("minishell", group->cmd[0], 2);
				perror("exec");
				//exit
			}
		}
	}
	else
		waitpid(0, NULL, 0);
}

void	simple_cmd(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	if (group->flag_fail)
		//exit
		return ;
	if (is_built(group->cmd[0]))
		ft_builtins(group, env_lst);
	else
		ft_bin(exec, group, env_lst);
	// close(exec->pfd_in);
	// close(exec->pfd_out);
	// exec->pfd_in = -1;
	// exec->pfd_out = -1;
}

//last command = first
//add print group
void	ft_exec(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	if (group->redir_in != NULL)
		redir_in(exec, group);
	else if (group->redir_out != NULL)
		redir_out(exec, group);
	else if (group->app_out != NULL)
		append_out(exec, group);
	if (group->next != NULL)
	{
		ft_pipe(exec);
		ft_exec(exec, group->next, env_lst);
	}
	if (group->next == NULL)
		simple_cmd(exec, group, env_lst);
}