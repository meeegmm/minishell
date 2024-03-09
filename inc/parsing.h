#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

////////////////// STRUCTS //////////////////

//tokenizer struct, ONLY FOR : cmd args ...

typedef enum
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APP_IN,
	APP_OUT,
	PIPE
} TokenType;

typedef struct s_tokens
{
	TokenType		type;
	char			*value;
	struct s_tokens	*next;
}					t_tokens;

////////////////// FONCTIONS //////////////////

//line parsing
char		**get_tab(t_tokens *list);
t_tokens	*lexer(char **token_tab);
int			syntax_pb(char *line);

//сheck cmd and files
char		**get_path(char **envp);
char		*path_check(char **path_list, char **args_list);
char		*cmd_check(char **cmd, char **envp);
int			get_tokens_nb(t_tokens *list);

//free
void		free_tokens(t_tokens *list);

//outils
void		print_cmd_tab(char **tab);
void		print_tab(char **tab);
void		print_env_list(t_list_env *list);
char		*ft_strdup(char *s1);
int			ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split1(char *str, int flag);

#endif