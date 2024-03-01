#include "../../inc/minishell.h"
#include "../../inc/parsing.h"
#include "../../inc/exec.h"


int	is_exit(const char *line)
{
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		return (0);
	else
		return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_group 	*group;
	t_tokens	*list;
	// int			cd;
	// int			pwd;
	// int			echo;
	char **token_tab;

	(void)ac;
	(void)av[0];
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		token_tab = ft_split1(line, 1);
		group = parser(line, envp);
		list = lexer(token_tab);
		if(group->flag_fail !=  0)
			line = NULL;
		else
		{
			printf("Parsed: ");
			print_tab(group->cmd);
			// printf("cmd[0]: ");
			// printf("%s\n", group->cmd[0]);
			// printf("list = : ");
			// print_list(list);
			// printf("env = : ");
			// printf("env == %s\n", envp[2]);
			builtin_pwd(list);
			// printf("pwd == %d\n", pwd);
			builtin_cd(list, group->cmd[1]);
			// printf("cd == %d\n", cd);
			builtin_echo(list);
			// printf("echo == %d\n", echo);
			builtin_env(list, group->cmd[0], envp);
			line = NULL;
		}
		line = readline(">$ ");
	}
	return 0;
}