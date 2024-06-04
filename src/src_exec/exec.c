/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:31:37 by memarign          #+#    #+#             */
/*   Updated: 2024/06/04 11:25:15 by memarign         ###   ########.fr       */
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
	// if (exec->pid == -1)
	// 	exec->pid = 0;
	// if (exec->pid == -1 || exec->pid == 0)
	if (exec->pid >= 0)
	{
		pid = exec->pid;
		// printf("BIN PID_START = %d\n\n", pid);
	}
	else
		pid = fork();
	// printf("BIN PID_START IF -1 = %d\n\n", pid);
	// printf("EXEC PFD_IN = %d\n", exec->pfd_in);
	// printf("EXEC PFD_OUT = %d\n\n", exec->pfd_out);
	if (pid == -1)
	{
		perror("Error exec fork");
		exit(EXIT_FAILURE);
	}
	// exec->pid = pid;
	// printf("BIN EXEC PID = %d\n\n", exec->pid);
	// printf("BIN EXEC PFD_IN = %d\n", exec->pfd_in);
	// printf("BIN EXEC PFD_OUT = %d\n\n", exec->pfd_out);
	if (pid == 0)
	{
		ft_redir(exec, group);
		// printf("BIN AFTER REDIR PID = %d\n", pid);
		// printf("BIN AFTER REDIR EXEC_PID = %d\n\n", exec->pid);
		// printf("AFTER FTREDIR exec: fd_in = %d\n", exec->fd_in);
		// printf("AFTER FTREDIR exec: fd_out = %d\n\n", exec->fd_out);
		// printf("BIN REDIR EXEC PFD_IN = %d\n", exec->pfd_in);
		// printf("BIN REDIR EXEC PFD_OUT = %d\n\n", exec->pfd_out);
		exec->stat = execve(group->cmd[0], group->cmd, envp);
		// printf("BIN AFTER EXEC PID = %d\n", pid);
		// printf("BIN AFTER EXEC EXEC_PID = %d\n\n", exec->pid);
		// printf("BIN AFTER EXEC PFD_IN = %d\n", exec->pfd_in);
		// printf("BIN AFTER EXEC PFD_OUT = %d\n\n", exec->pfd_out);
	// 	if (execve(group->cmd[0], group->cmd, envp) == 0)
	// 	{
	// 		if (access(group->cmd[0], F_OK | X_OK) == -1)
	// 		{
	// 			free_tab(envp);
	// 			return(126);
	// 		}
	// 	}
	}
	else
		waitpid(pid, NULL, 0);
	// printf("BIN AFTER WAIT PID = %d\n", pid);
	// printf("BIN AFTER WAIT EXEC_PID = %d\n\n", exec->pid);
	free_tab(envp);
	// printf("AFTER EXEC: fd_in = %d\n", exec->fd_in);
	// printf("AFTER EXEC: fd_out = %d\n\n", exec->fd_out);
	// printf("AFTER WAIT PF_DIN = %d\n\n", exec->pfd_in);
	// printf("AFTER WAIT PFD_OUT = %d\n\n", exec->pfd_out);
	return (exec->stat);
}

int	simple_cmd(t_exec *exec, t_group *group, t_list_env *env_lst)
{
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
		ft_redir(exec, group);
		// printf("BEFORE BUILT EXEC PID = %d\n", exec->pid);
		exec->stat = ft_builtins(exec, group, env_lst);
		// printf("AFTER BUILT EXEC PID = %d\n", exec->pid);
		// reset_fds(exec);
	}
	else
		ft_bin(exec, group, env_lst);
	return (exec->stat);
}

