#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"
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

typedef struct s_remove
{
	int i;
	int k;
	int len;
} t_remove;

typedef struct s_tokens
{
	TokenType type;
	char *value;
	struct s_tokens *next;
} t_tokens;

typedef struct s_tokenizer
{
	int len;
	int i;
	int k;
	char *new;
} t_tokenizer;

typedef struct s_parser
{
	char **token_tab;
	t_tokens *token_list;
	char *line;
} t_parser;


////////////////// FONCTIONS //////////////////

//line parsing
// char	**get_tab(t_tokens *list);
//int		syntax_pb(char *line);
void print_token_list(t_tokens *list);

//parser_outils
int    is_built(char *str);
int only_spaces(char *str);
int is_folder(char *line);
t_parser *create_init_p (void);
t_group *create_init_group(void);
char **spaces_between_quotes(char ***tab);
int quotes_ok(char **str);
char *no_quotes(char *str, char c);
char	*add_spaces(char **tmp);

//expand
int delimiter_nb(char *str);
t_tokenizer *init_data(char *s);
void between_single(t_tokenizer *d, char *s);
void	before_expand_or_special(t_tokenizer *d, char *s);
char *temp_tokenizer(char *str);
char *no_quotes(char *str, char c);
int spaces_nb(char *str);
char *with_28(char **str);
int is_meta(char *str);

//token_list
int syntax_pb(t_tokens *list);
t_tokens *lexer(char **token_tab);
char	*ft_expand(char *str, t_list_env *env);
char *quotes_expand(char *str, t_list_env *env);

//get_group
void invalid_group(t_group *group, int flag);
t_group *get_group_list(t_tokens *list, t_list_env *env);
t_group *create_init_group(void);
t_group	*get_group(t_tokens *list, t_list_env *env);


//сheck cmd and files
int	cmd_check(char **str, t_list_env *env);
char **get_cmd_tab(t_tokens *list);
int get_files(t_tokens *list, t_group *group);
void	create_file(char *str);
void	permission_pb_msg(char *str);
void	existence_pb_msg(char *str);

//free
void free_tokens(t_tokens *list);
void free_t_parser(t_parser *p);

//outils
void	print_tab(char **tab);
void	print_list(t_list_env *list);
void	print_group(t_group *group);
char	*ft_strdup(char *s1);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin1(char *s1, char *s2);
char	**ft_split1(char *str, int flag);
char	**copy_tab(char **tab);
void	ft_putstr_err(char *str);
char	*from_tab_to_line(char **tab);
int		is_digit(char c);
int		is_alpha(char c);
int is_special(char c);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);


#endif