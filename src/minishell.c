#include "../inc/minishell.h"

int	main(void)
{
	const char	*line;

	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		printf("%s\n", line);
		// free(line);
		// rl_clear_history();
		line = readline(">$ ");
	}
}
