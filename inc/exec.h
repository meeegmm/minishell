#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

////////////////// BUILT_INS //////////////////
int		builtin_echo(t_tokens *list);
int		builtin_pwd(t_tokens *list);
int		builtin_cd(t_tokens *list, char *path);
int		builtin_env(t_tokens *list, char *path, char **envp);


////////////////// EXEC (PIPEX) //////////////////
void	do_cmd(char *token, char **envp);
void	cmd1(char **av, int *pipe_fd, char **envp);
void	cmd2(char **av, int *pipe_fd, char **envp);


////////////////// REDIRECTION //////////////////


////////////////// SIGNALS //////////////////


////////////////// CHECKS //////////////////


////////////////// UTILS //////////////////

//built_ins
char	*set_dir(char *path);

//exec

//redirection  (for now = PIPEX)
int		open_file(char *file, int std_no);

//signals

//libft
char	**ft_split(char *s, char c);
void	ft_putstr_fd(char *s, int fd);

#endif