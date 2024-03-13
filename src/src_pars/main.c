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
	t_group		*group;
	char		**new_envp;

	(void)ac;
	(void)av[0];
	new_envp = set_envp(envp);
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		group = parser(line, new_envp);
		if (group->flag_fail != 0)
			line = NULL;
		else
		{
			// printf("Parsed: ");		
			// print_tab(group->cmd);
			simple_cmd(group, new_envp);
			line = NULL;
		}
		line = readline(">$ ");
	}
	return (0);
}
