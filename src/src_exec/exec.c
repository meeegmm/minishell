/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:31:37 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 21:04:12 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

//add printf
//add checks
//think about exit
int	ft_bin(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	char	**envp;
	pid_t	pid;

	envp = get_envp(env_lst);

	if (exec->pid >= 0)
	{
		pid = exec->pid;
		// printf("BIN PID_START = %d\n\n", pid);
	}
	else
		pid = fork();
	if (pid == -1)
	{
		perror("Error exec fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ft_redir(exec, group);
		exec->stat = execve(group->cmd[0], group->cmd, envp);
	}
	else
		waitpid(pid, NULL, 0);
	free_tab(envp);
	return (exec->stat);
}

int	simple_cmd(t_exec *exec, t_group *group, t_list_env **env_lst)
{
	t_built	fd;
	char **tab;

	if (group->app_in != NULL)
	{
		tab = get_here_doc(exec, group);
		if (!group->cmd)
		{
			free_tab(tab);
			return (0);
		}
		else
		{
			here_doc(exec, group);
			free_tab(tab);
			return (0);
		}
	}
	if (!group->cmd)
	{
		ft_redir2(exec, group);
		return (0);
	}
	if (is_built(group->cmd[0]))
	{
		ft_redir_b(exec, group, &fd);
		exec->stat = ft_builtins(exec, group, env_lst, &fd);
	}
	else
		ft_bin(exec, group, *env_lst);
	return (exec->stat);
}
