#include "../../inc/exec.h"

//TODO: assign good exit status if fail
//		choose a function for error messages to write on good fd
//		handle args
//		one builtinins function for all w/ checks and free
//		handle if env or path is unset
//		pass by tmp for each?

//__echo__
//output the args, separated ' ' end by /n witout -n
int	builtin_echo(t_tokens *list)
{
	int	option;

	option = 0;
	if (ft_strncmp(list->value, "echo", 4)  == 0 && list->next != NULL)
	{
		if (ft_strncmp(list->next->value, "-n", 2) == 0)
		{
			option = 1;
			list = list->next->next;
		}
		else
			list = list->next;
		while (list != NULL)
		{
			printf("%s", list->value);
			printf(" ");
			list = list->next;
		}
		if (!option)
			printf("\n");
		return (0);
	}
	return (-1);
}


// __pwd__Use char *getcwd(char *buf, size_t size)
//display current directory
int	builtin_pwd(t_tokens *list)
{
	char	*dir;
	char	*buf;
	size_t	size;

	size = 2048; //look for max or string size?
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (-2);
	if (ft_strncmp(list->value, "pwd", 3)  == 0)
	{
		dir = getcwd(buf, size);
		free(buf);
		printf("%s", dir);
		printf("\n");
		return (0);
	}
	return (-1);
}


//__cd__Use chdir(path)
// display pwd if ../../etc?
//doesn't work if tab to fill path
int	builtin_cd(t_tokens *list, char *path)
{
	// char	*buf;
	// size_t	size;

	// size = 2048; //look for optimal value
	// buf = malloc(sizeof(char) * (size + 1));
	// if (!buf)
	// 	return (-2);
	if (ft_strncmp(list->value, "cd", 2) == 0)
	{
		if (list->next == NULL || ft_strncmp(list->next->value, "~", 1) == 0)
			path = set_dir("HOME");
		if (access(path, F_OK | X_OK) == 0)
			chdir(path);
		// if (ft_strncmp(list->next->value, "..", 2) == 0)
		// 	{		
		// 		path = getcwd(buf, size);
		// 		free(buf);
		// 	}
		ft_putstr_fd("Current directory: ", 1);			
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (-1); 
}

//__env__
//w/ args, change the cmd or pgm env
int	builtin_env(t_tokens *list, char *path, char **envp)
{
	t_tokens	*env_list;

	env_list = lexer(envp);
	if (ft_strncmp(list->value, "env", 3) == 0 && list->next == NULL)
	{
		if (access(path, F_OK | X_OK) == 0)
		{
			while (env_list != NULL)
			{
				printf("%s", env_list->value);
				printf("\n");
				env_list = env_list->next;
			}
			free_tokens(env_list);
			return (0);
		}
	}
	return (1);
}

//__export__
//set export attibuts (= make var available for child processes)
//need to get current process
//duplicate in a tab, set this tab as **envp, add if "export"
//w/out options, export all var + display env list
//free when process ends
//__unset__
//unset + args (= variables)
//substract from export tab
//check when special variable

//__exit__
//end the process
//process then only contain return status
//go to parent or end shell


