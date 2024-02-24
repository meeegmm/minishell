#include "../../inc/exec.h"

int	main(void)
{
	const char	*line;

	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		printf("%s\n", line);
		line = readline(">$ ");
	}
	// free(line);
	// rl_clear_history();
}
