#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

////////////////// STRUCTS //////////////////

//parsed ligne struct : REDO!!

typedef struct s_group
{
int flag_fail;
char **cmd; 
char *redir_in;
char *redir_out;
char *app_out;
// app_in (heredoc)
struct s_group *next;
} t_group;


typedef struct s_list_env
{
	char *key;
	char *value;
	struct s_list_env *next;
} t_list_env;


typedef struct s_exec
{
	// struct s_group		*group;
	// struct s_list_env	*env_lst;
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
t_group *parser(char *line, char **envp);
t_group *invalid_group(int flag);

//envp parsing
t_list_env *get_list(char **tab);
char **get_envp(t_list_env *list);

//free
void free_tab(char **tab);
void free_envp_list(t_list_env *list);
void free_group_list(t_group *group);

#endif