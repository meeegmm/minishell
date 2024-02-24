#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

////////////////// STRUCTS //////////////////

//tokenizer struct, ONLY FOR : cmd args ...

typedef enum 
{
	WORD,
	SEP,
} TokenType;

typedef struct s_tokens
{
	TokenType type;
	int len; //нужно ли это?
	char *value;
	struct s_tokens *next;
} t_tokens;


////////////////// FONCTIONS //////////////////

//line parsing
char **get_tab(t_tokens *list);

//сheck cmd and files
char	**get_path(char **envp);
char	*path_check(char **path_list, char **args_list);
char	*cmd_check(char **cmd, char **envp);

//free
void free_tokens(t_tokens *list);

//outils
void	print_tab(char **tab);
void	print_list(t_list_env *list);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split1(char *str, int flag);

#endif