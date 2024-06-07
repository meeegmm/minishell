/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:48 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 22:32:22 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//doesn't close well when pipe
void	child_pid(t_exec *exec, int *pipe_fd)
{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(pipe_fd[0], 0); //STDIN_FILENO
		exec->pfd_in = pipe_fd[0];
}
void	parent_pid(t_exec *exec, int *pipe_fd)
{
		waitpid(-1, NULL, 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(pipe_fd[1], 1); //STDOUT_FILENO
		exec->pfd_out = pipe_fd[1];
}
void		ft_pipe(t_exec *exec)
{
	pid_t	pid;
	int		pipe_fd[2];

	// pipe(pipe_fd);
	if (pipe(pipe_fd))
		return ; // -1?
	pid = fork();
	if (pid == -1)
	{
		//return (1);
		perror("Error ft_pipe");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		dup2(exec->pfd_out, 1);
		close(pipe_fd[0]);
		exec->pfd_in = pipe_fd[0];
		exec->pid = -1;
	}
	else
	{
		close(pipe_fd[0]);
		exec->pfd_out = pipe_fd[1];
		close( pipe_fd[1]);
	}
//	else
//	{
//		waitpid(-1, NULL, 0);
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
//		dup2(pipe_fd[1], 1);
//		exec->pfd_out = pipe_fd[1];
//		exec->pid = pid;
//	}
}

//Faire attention au IN et au OUT des differents forks 
// soit en dup() puis retablir soit "is_pipe" puis revenir sur IN au besoin ou redir

//
//boucle sur toutes les commandes
//si command de next creer un pipe
//dans le child si la commande est la 1er ne pas dup stdin
//dup stdout avec le pipe[1] sauf si la commande est la derniere
//si la commande n'est pas la premiere tu dup stdin avec le pipe[0] qui a ete sauvegarde precedement
//dans le parent
//sauvegarder le pipe[0] pour la prochaine qui lui servira d'infile
//wait uniquement qund toutes les commandes ont ete lancees 
//sauvegarder tout les pids
//ne conserver aue la valeur de retour de la derniere cmd pour la glbl

//dup ave pipe apres dup des redir
