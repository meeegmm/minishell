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
	// int			cd;
	// int			pwd;
	// int			echo;

	(void)ac;
	(void)av[0];
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		group = parser(line, envp);
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
			built_cd(group->cmd[0], group->cmd[1]);
			// printf("cd == %d\n", cd);
			built_pwd(group->cmd[0]);
			// printf("pwd == %d\n", pwd);
			built_echo(group);
			// printf("echo == %d\n", echo);
			line = NULL;
		}
		line = readline(">$ ");
	}
	return 0;
}