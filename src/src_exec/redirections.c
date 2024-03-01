#include "../../inc/exec.h"

//___PIPEX___ pipes + redirections for simple cmd

// void	cmd1(char **av, int *pipe_fd, char **envp)
// {
// 	int	fd;

// 	fd = open_file(av[1], 0);
// 	dup2(fd, STDIN_FILENO);
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	close(fd);
// 	do_cmd(av[2], envp);
// }

// void	cmd2(char **av, int *pipe_fd, char **envp)
// {
// 	int	fd;

// 	fd = open_file(av[4], 1);
// 	dup2(fd, STDOUT_FILENO);
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	close(fd);
// 	close(pipe_fd[0]);
// 	do_cmd(av[3], envp);
// }

// int	main(int ac, char **av, char **env)
// {
// 	int	pipe_fd[2];
// 	int	pid;
// 	int	pid2;

// 	if (ac != 5)
// 	{
// 		ft_putstr_fd("Must contain: ./pipex file1 cmd1 cmd2 file2", 2);
// 		exit(0);
// 	}
// 	if (pipe(pipe_fd) == -1)
// 		exit (-1);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(-1);
// 	if (pid == 0)
// 		cmd1(av, pipe_fd, env);
// 	close(pipe_fd[1]);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		exit(-1);
// 	if (pid2 == 0)
// 		cmd2(av, pipe_fd, env);
// 	close(pipe_fd[0]);
// 	wait(NULL);
// 	wait(NULL);
// }