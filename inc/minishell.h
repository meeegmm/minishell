/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:47:16 by memarign          #+#    #+#             */
/*   Updated: 2024/04/30 09:52:21 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

////////////////// STRUCTS //////////////////

//parsed ligne struct : REDO!!

typedef struct s_group
{
	int				flag_fail;
	char			**cmd;
	char			*redir_in;
	char			*redir_out;
	char			*app_out;
	char			*app_in;
	struct s_group	*next;
}					t_group;

typedef struct s_list_env
{
	char				*key;
	char				*value;
	struct s_list_env	*next;
}						t_list_env;

typedef struct s_exec
{
	int				status;
	int				infile;
	int				outfile;
	int				fd_in;
	int				fd_out;
	int				pfd_in;
	int				pfd_out;
	pid_t			pid;
}	t_exec;

////////////////// FONCTIONS //////////////////

//parsing
int			only_spaces(char *str);
t_group		*parser(char *input, t_list_env *env);

//envp parsing
char		**get_envp(t_list_env *list);
t_list_env	*get_list(char **tab);
t_list_env	*env_lst_sos(void);

//exec
void		minish(t_exec *exec, t_group *group, t_list_env *env);
void		reset_minish(t_exec *exec, t_group *start);
void		ft_redir(t_exec *exec, t_group *group);
void		ft_pipe(t_exec *exec);
void		simple_cmd(t_exec *exec, t_group *group, t_list_env *env_lst);
void		end_minish(t_exec *exec, t_group *group, t_list_env *env);
void		builtin_exit(t_exec *exec, t_group *group, t_list_env *env_lst);

//fd
void		init_exec(t_exec *exec);
void		close_fds(t_exec *exec);
void		set_io(t_exec *exec);
void		init_std(t_exec *exec);
void		close_std(t_exec *exec);

//free
void		free_tab(char **tab);
void		free_envp_list(t_list_env *list);
void		free_group_list(t_group *group);

int			ft_strncmp(const char *s1, const char *s2, int n);
void		print_list(t_list_env *list);
char		*get_key(char *str);
char		*get_value(char *str);
int			ft_strlen(const char *s);
char		*ft_strdup(char *s1);

#endif