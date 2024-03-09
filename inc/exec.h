#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

//TODO:
//redir struct
//exec struct

////////////////// BUILT_INS //////////////////
int		builtin_echo(t_tokens *token_lst);
int		builtin_pwd(t_tokens *token_lst);
int		builtin_cd(t_tokens *token_lst, char *path);
int		builtin_env(t_tokens *token_lst, char **envp);
void	ft_builtins(t_tokens *token_lst, t_group *group, char **envp);

////////////////// EXEC //////////////////
void	simple_cmd(t_tokens *token_lst, t_group *group, char **envp);
void	ft_s_exec(t_tokens *token_lst, t_group *group, char **envp);
void	ft_r_exec(t_tokens *token_lst, t_group *group, char **envp);

////////////////// REDIRECTION //////////////////
void	ft_redir(t_tokens *token_lst, t_group *group, int *pipe_fd, char **envp);

////////////////// SIGNALS //////////////////

////////////////// CHECKS //////////////////

////////////////// UTILS //////////////////

//built_ins
char	*set_dir(char *path);
int		is_built(char *str);

//exec
char	**set_envp(char **envp);

//redirection  (for now = PIPEX)
int		open_file(char *file, int std_no);

//signals

//libft
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *cmd, char *s, int fd);

#endif