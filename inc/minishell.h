#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_lg
{
	char		*key;
	char		*value;
	struct s_lg	*next;
}				t_lg;

typedef struct s_parsed
{
	struct s_lg		t_list_lg;
	struct s_parsed	*next;
}					t_parsed;

// pipe struct

/*typedef struct s_pipe
{
	int		fd_p[2];
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipe;*/

//struct after the parsing

/*enum in
{
    REDIR_IN,
    APP_IN,
    ZERO_IN
};

enum out
{
    REDIR_OUT,
    APP_OUT,
    ZERO_OUT
};*/

typedef struct s_logic_grp
{
	int					flag_fail;
	char				**cmd;
	//enum redir_in;
	//enum redir_out;
	char				**source;
	char				**destination;
	struct s_logic_grp	*next;
}					t_logic_grp;

// struct s_list для оболочки

typedef struct s_list_env
{
	char				*key;
	char				*value;
	struct s_list_env	*next;
}						t_list_env;

// struct для exec части

//typedef int (*t_builtin_ptr)(t_logic_groupe*, t_exec*);

typedef struct s_exec
{
	//t_builtin_ptr	builtins[7];
	t_list_env		*envp_list;
	//int			status;
	//char			exit_f;
}					t_exec;


//envp parsing
t_list_env	*get_list(char **tab);
char		**get_tab(t_list_env *list);

//builtins prototypes
int			ft_pwd(t_list_env *list);
int			ft_export(t_list_env *list, char *to_key, char *to_value);
int			ft_env(t_exec *p);

//exec
int			exec(t_logic_grp *lg, t_exec *p);

char		**get_path(char **envp);
char		*path_check(char **path_list, char **args_list);
char		*cmd_check(char **cmd, char **envp);

//free
void		free_tab(char **tab);
void		free_list(t_list_env *list);
void		free_logic_group(t_logic_grp *lg);
void		free_struct_exec(t_exec *p);

//checks
int			is_exit(const char *line);

//outils
char		**ft_split1(char *str, int flag);
char		*ft_strdup(char *s1);
int			ft_strlen(char *s);
int			ft_strncmp(char *s1, char *s2, int n);
void		print_tab(char **tab);
void		print_list(t_list_env *list);
char		*ft_strjoin(char *s1, char *s2);

#endif