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
	t_list_env	*env_lst;
	t_tokens	*token_lst;
	char		**token_tab;

	(void)ac;
	(void)av[0];
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		token_tab = ft_split1(line, 1);
		group = parser(line, envp);
		env_lst = get_list(envp);
		token_lst = lexer(token_tab);
		if (group->flag_fail != 0)
			line = NULL;
		else
		{
			// printf("Parsed: ");
			// print_cmd_tab(group->cmd);
			if (!is_built(token_lst->value))
				ft_builtins(token_lst, group, envp);
			else
				ft_exec(group, envp);
			line = NULL;
		}
		line = readline(">$ ");
	}
	return (0);
}
