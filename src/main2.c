#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_group *group;

	(void)ac;
	(void)av[0];
	//$SHLVL
	line = readline(">$ ");
	while (1)
	{
		if (line && *line)
			add_history(line);
		
		group = parser(line, envp);
		if(!group) //???
		{
			free(line);
			line = NULL; //нужно ли это?
		}
		else
		{

			while(group != NULL)
			{
				if(group->flag_fail == 258 || (group->flag_fail == 127 && group->next == NULL))
				{
					free(line);
					line = NULL; //нужно ли это?
				}
				else if(group->flag_fail == 0) //будет ли проверяться второе условие?
				{
					//execve
				}
				//
				printf("Parsed :\n");
				print_group(group);
				printf("\n");
				group = group->next;
			}
		}
		line = readline(">$ ");
	}
	return 0;
}