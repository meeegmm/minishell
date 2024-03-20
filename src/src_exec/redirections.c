#include "../../inc/exec.h"

//!! si redir = deja fork
//always connect before I/O redir
//open then dup(2)
//do it for all redir
//exec

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
