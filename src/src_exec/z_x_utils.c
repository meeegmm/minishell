/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_x_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madmeg <madmeg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 04:11:49 by memarign          #+#    #+#             */
/*   Updated: 2024/06/09 12:15:41 by madmeg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	group_nbr(t_group *head)
{
	t_group *current;
	int	size;

	current = head;
	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

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

//create pipes
//pas la première, jusqu'à l'avant dernière out du précédent = in du suivant
//fork and execute
//close pipes
//free group