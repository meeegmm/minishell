#include "../inc/minishell.h"

// lg struct init

t_logic_groupe *get_lg(t_logic_groupe *lg)
{
	lg->cmd = malloc(sizeof(char*) * 2);

	lg->flag_fail = 0;

	lg->cmd[0] = ft_strdup("pwd"); // ls работает в bash (/bin/ls в том числе), но почему-то не работает в zsh
	if(lg->cmd[0] == NULL)
	{
		free(lg->cmd);
		free(lg);
		return (NULL);
	}
	//lg->cmd[1] = ft_strdup("-l");
	//lg->cmd[2] = ft_strdup("Makefile");
	lg->cmd[1] = NULL;

	lg->source = NULL;
	lg->destination = NULL;

	return (lg);
}

// exec struct init

t_exec *get_exec_struct(t_exec *p, char **envp)
{
	p->envp_list = get_list(envp);
	return(p);
}


int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*env_list;

	(void) ac;
	(void) av;
	(void) env;
	if (isatty(STDIN_FILENO) == 0)
	{
		perror("minishell> ");
		return (1);
	}
	//protection si !env ? + que faire avec env
	env_list = get_env(env);
	free_env(&env_list);
	while (1)
	{
		input = readline("minishell> ");
		if (check_syntax (input) == NULL)
			return (0);
		//ft_expansion(input, env_list);
		free(input);
	}
	free(input);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_exec *p;
	t_logic_groupe *lg;

	p = NULL; //важно ли это?
	lg = NULL;

	if(ac < 1)
	{
		exit(EXIT_FAILURE);
	}
	printf("%s\n", av[0]); //sinon unused

	////

	/*char *buf = NULL;
	size_t	buf_size = 2048;

	buf = malloc(sizeof(char) * buf_size);
	if (buf == NULL) {
		perror("Malloc");
		return (EXIT_FAILURE);
	}
	while(1)
	{*/
		//buf = readline("minishell$ ");

		p = malloc(sizeof(t_exec));
		if(!p)
		{	
			//free(buf);
			exit(EXIT_FAILURE);
		}
		p = get_exec_struct(p, envp);

		lg = malloc(sizeof(t_logic_groupe)); //не уверена, что это правильная форма записи
		if(!lg)
		{
			free_struct_exec(p);
			//free(buf);
			exit(EXIT_FAILURE);
		}
		lg = get_lg(lg); //	what if NULL

		//printf("%s\n", lg->cmd[0]); print cmd name

		exec(lg, p);

		free_logic_group(lg);
		free_struct_exec(p); //вызывает сегфолт

		//free(buf);
	return (0);
}