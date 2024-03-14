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
//define error messages + code (exit status)
//check flag fail, if 1 = fail
//new_envp must not be in main!

////////////////// BUILT_INS //////////////////
int			builtin_echo(t_group *group);
int			builtin_pwd(t_group *group);
int			builtin_cd(t_group *group, char *path, t_list_env *env_lst);
int			builtin_env(t_group *group, t_list_env *env_lst);
int			builtin_export(t_group *group, t_list_env *env_lst);
void		ft_builtins(t_group *group, t_list_env *env_lst);

////////////////// EXEC //////////////////
void		simple_cmd(t_group *group, char **envp);
void		ft_s_exec(t_group *group, char **envp);
void		ft_r_exec(t_group *group, char **envp);

////////////////// REDIRECTION //////////////////
// void	ft_redir(t_tokens *token_lst, t_group *group, int *pipe_fd, char **envp);

////////////////// SIGNALS //////////////////

////////////////// CHECKS //////////////////

////////////////// UTILS //////////////////

//built_ins
char		*set_dir(t_list_env *env_lst, char *key);
char		*mod_var(t_list_env *env_lst, char *key, char *new_value);
int			is_built(char *str);

//exec
char		**set_envp(char **envp);
char		**split_cmds(char *line);

//redirection  (for now = PIPEX)
int			open_file(char *file, int std_no);

//signals

//libft
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *cmd, char *s, int fd);
int			is_char(char *str, char c);
int			tab_size(char **tab);
void		print_token_lst(t_tokens *token_lst);

#endif