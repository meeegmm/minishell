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
	t_tokens	*token_lst;
	char		**new_envp;
	char		**token_tab;

	(void)ac;
	(void)av[0];
	new_envp = set_envp(envp);
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		token_tab = ft_split1(line, 1);
		group = parser(line, new_envp);
		token_lst = lexer(token_tab);
		if (group->flag_fail != 0)
			line = NULL;
		else
		{
			// printf("Parsed: ");		
			// print_tab(group->cmd);
			simple_cmd(token_lst, group, new_envp);
			line = NULL;
		}
		line = readline(">$ ");
	}
	return (0);
}
