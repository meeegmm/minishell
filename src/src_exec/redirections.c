#include "../../inc/exec.h"

//Use int is_meta(char c)
//always connect before I/O redir
//open then dup(2)
//do it for all redir
//exec

// void	ft_pipes(t_tokens *token_lst, t_group *group, int *pipe_fd, char **envp)
// {
// 	int	pid;

// 	if (pipe(pipe_fd) == -1)
// 		exit (-1);
// 	pid = fork();
// 	if (token_lst->type == REDIR_IN)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		ft_s_exec(token_lst, group, envp);
// 	}
// 	else if (token_lst->type == REDIR_OUT)
// 	{
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		ft_s_exec(token_lst, group, envp);
// 	}
// 	else
// 		exit(1);
// }

// void	ft_r_exec(t_tokens *token_lst, t_group *group, char **envp)
// {
// 	int	pipe_fd[2];
// 	int	pid;

// 	if (pipe(pipe_fd) == -1)
// 		exit (-1);
// 	pipe_fd[0] = open_file(token_lst->next->value, 0);
// 	pipe_fd[1] = open_file(token_lst->next->value, 1);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(-1);
// 	if (pid == 0)
// 		ft_redir(token_lst, group, pipe_fd, envp);
// }
