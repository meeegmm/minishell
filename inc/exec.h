#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

// typedef struct s_exec
// {
// 	char		*path;
// 	char 		**env;
// 	t_group 	*group;
// 	t_token_env	*env_list;
// 	t_tokens	*tokens;
// } 				t_exec;

////////////////// BUILT_INS //////////////////
int		builtin_echo(t_tokens *token_lst);
int		builtin_pwd(t_tokens *token_lst);
int		builtin_cd(t_tokens *token_lst, char *path);
int		builtin_env(t_tokens *token_lst, char *path, char **envp);
void	ft_builtins(t_tokens *token_lst, t_group *group, char **envp);

////////////////// EXEC //////////////////
void	ft_exec(t_group *group, char **envp);

////////////////// REDIRECTION //////////////////
void	r_exec(t_group *group, char **envp);

////////////////// SIGNALS //////////////////

////////////////// CHECKS //////////////////

////////////////// UTILS //////////////////

//built_ins
char	*set_dir(char *path);
int		is_built(char *str);

//exec

//redirection  (for now = PIPEX)
int		open_file(char *file, int std_no);

//signals

//libft
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);

#endif