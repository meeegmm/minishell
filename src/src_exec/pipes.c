// #include "../../inc/exec.h"
// #include "../../inc/parsing.h"

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
// 		ft_s_exec(token_lst, group);
// 	}
// 	else if (token_lst->type == REDIR_OUT)
// 	{
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		ft_s_exec(token_lst, group);
// 	}
// 	else
// 		exit(1);
// }
