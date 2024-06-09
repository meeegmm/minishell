/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madmeg <madmeg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:48 by memarign          #+#    #+#             */
/*   Updated: 2024/06/09 12:17:44 by madmeg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

// void	child_pid(t_exec *exec, int *pipe_fd)
// {
// 		close(pipe_fd[1]);
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[0], 0); //STDIN_FILENO
// 		exec->pfd_in = pipe_fd[0];
// }
// void	parent_pid(t_exec *exec, int *pipe_fd)
// {
// 		waitpid(-1, NULL, 0);
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[1], 1); //STDOUT_FILENO
// 		exec->pfd_out = pipe_fd[1];
// }
// void		ft_pipe(t_exec *exec, t_group *group)
// {
// 	int size;

// 	size = group_size(group) - 1; //add
// 	pid_t	pid;
// 	int		pipe_fd[2];

// 	if (pipe(pipe_fd) == -1)
// 		return ; // error function
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		//return (1);
// 		perror("Error ft_pipe"); //error function?
// 		exit(-1); // changed from failure to -1
// 	}
// 	if (pid == 0)
// 	{
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], 0);
// 		dup2(exec->pfd_out, 1);
// 		close(pipe_fd[0]);
// 		exec->pfd_in = pipe_fd[0];
// 		exec->pid = -1;
// 	}
// 	else
// 	{
// 		close(pipe_fd[0]);
// 		exec->pfd_out = pipe_fd[1];
// 		close( pipe_fd[1]);
// 	}
//	else
//	{
//		waitpid(-1, NULL, 0);
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
//		dup2(pipe_fd[1], 1);
//		exec->pfd_out = pipe_fd[1];
//		exec->pid = pid;
//	}
// }

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

//create pipes
//pas la première, jusqu'à l'avant dernière out du précédent = in du suivant
//fork and execute
//close pipes
//free group

void ft_pipe(t_group *group, int num_commands)
{
    int pipe_fd[2];
    int prev_in = STDIN_FILENO;  // Input for the first command is standard input
    t_group *current = group;
    int i = 0;

    while (current != NULL)
	{
        if (current->next != NULL)
		{  // If there is another command
            if (pipe(pipe_fd) == -1)
			{
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
		else 
		{
            // Last command, no need to create a pipe
            pipe_fd[1] = STDOUT_FILENO;
        }
        pid_t pid = fork();
        if (pid == 0)
		{  // Child process
            // Redirect input
            if (prev_input != STDIN_FILENO)
			{
                dup2(prev_input, STDIN_FILENO);
                close(prev_input);
            }
            // Redirect output
            if (pipe_fd[1] != STDOUT_FILENO)
			{
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (pipefd[0] != STDIN_FILENO)
                close(pipefd[0]);
            execute_command(current, STDIN_FILENO, STDOUT_FILENO);
        } 
		else if (pid > 0)
		{  // Parent process
            // Close write end of the pipe in the parent
            if (pipe_fd[1] != STDOUT_FILENO)
                close(pipe_fd[1]);
            if (prev_input != STDIN_FILENO)
                close(prev_input);
            prev_input = pipe_fd[0];  // The read end of the current pipe will be the input for the next command
        }
		else
		{
            perror("fork");
            exit(EXIT_FAILURE);
        }
	}
    current = current->next;
	i++;
}

// void		ft_pipe(t_exec *exec, t_group *group, t_cmd *cmd_pipe)
// {
// 	t_group	*current;
// 	int		pipe_fd[2];

// 	current = group;
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("error pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		pipe_fd[1] = 1;
// 	if (cmd_pipe->pid == 0)
// 	{
// 		dup2(exec->fd_in, 0);
// 		dup2(cmd_pipe->pfd, 1); //pipe_fd[1]
// 		close(pipe_fd[0]);
// 			// exec->pfd_in = pipe_fd[0];
// 			// exec->pid = -1;
// 	}
// 	else
// 	{
// 		dup2(exec->fd_out, 1);
// 		dup2(cmd_pipe->prev_in, 0); //pipe_fd[0]
// 		close(pipe_fd[1]);
// 	}
// 	while() //size > size - 1 
// 		waitpid(command->pid, NULL, 0);
// 	// command = command->next;
// }