#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

////////////////// STRUCTS //////////////////

//parsed ligne struct : REDO!!

// enum in
// {
//     REDIR_IN,
//     APP_IN,
//     ZERO_IN
// };

// enum out
// {
//     REDIR_OUT,
//     APP_OUT,
//     ZERO_OUT
// };

typedef struct s_group
{
int flag_fail;
char **cmd; 
// enum redir_in;
// enum redir_out;
char **source; 			//reassigner la 1re ligne par la derniere et free le reste
char **destination;
struct s_group *next;
} t_group;


typedef struct s_list_env
{
	char *key;
	char *value;
	struct s_list_env *next;
} t_list_env;

////////////////// FONCTIONS //////////////////

//parsing
t_group *parser(char *line, char **envp);

//envp parsing
t_list_env *get_list(char **tab);
char **get_envp(t_list_env *list);

//free
void free_tab(char **tab);
void free_envp_list(t_list_env *list);
void free_group(t_group *lg);

#endif