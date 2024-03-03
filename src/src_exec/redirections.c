#include "../../inc/exec.h"

//___PIPEX___ pipes + redirections for simple cmd

//always connect before I/O redir
//dup() before redir to save fd
//open then dup(2)
//do it for all redir
//close() where necessary
//dup(2) to remove redir
//exec

// void	ft_redir(char *path, char **args, char **envp, int fd)
// {
// 	int	pipe_fd[2];
// 	int	pid;

// 	if (pipe(pipe_fd) == -1)
// 		exit (-1);
// 	pid = fork();
// 	if (pid)
// 	{
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		wait(&pid);
// 	}
// 	else
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDIN_FILENO);
// 	}
// 	if (fd)
// 		ft_exec(path, envp);
// 	else
// 		exit(1);
// }

// void	r_exec(t_group *group, t_tokens *list, char **envp)
// {
// 	int	pipe_fd[2];

// 	pipe_fd[0] = open_file(list->next->value, 0);
// 	pipe_fd[1] = open_file(list->next->value, 1);
// 	if (pipe(pipe_fd) == -1)
// 		exit (-1);
	

// }