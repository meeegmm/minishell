#include "../../inc/exec.h"

//TODO: assign good exit status if fail
//		choose a function for error messages to write on good fd
//		handle args
//		one builtins function for all w/ checks and free
//		handle if env or path is unset
//		pass by tmp for each?

//__echo__
//output the args, separated ' ' end by /n witout -n
int	builtin_echo(t_tokens *token_lst)
{
	int	option;

	option = 0;
	if (ft_strncmp(token_lst->value, "echo", 4) == 0 \
									&& token_lst->next != NULL)
	{
		if (ft_strncmp(token_lst->next->value, "-n", 2) == 0)
		{
			option = 1;
			token_lst = token_lst->next->next;
		}
		else
			token_lst = token_lst->next;
		while (token_lst != NULL)
		{
			printf("%s", token_lst->value);
			printf(" ");
			token_lst = token_lst->next;
		}
		if (!option)
			printf("\n");
		return (0);
	}
	return (1);
}

// __pwd__Use char *getcwd(char *buf, size_t size)
//display current directory
int	builtin_pwd(t_tokens *token_lst)
{
	char	*dir;
	char	*buf;
	size_t	size;

	size = 2048; //look for optimal value
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (-2);
	if (ft_strncmp(token_lst->value, "pwd", 3) == 0)
	{
		dir = getcwd(buf, size);
		printf("%s", dir);
		printf("\n");
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

//__cd__Use chdir(path)
//doesn't work if tab to fill path
//create and keep subshells, why
int	builtin_cd(t_tokens *token_lst, char *path)
{
	char	*buf;
	size_t	size;

	size = 2048; //look for optimal value
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (2);
	if (ft_strncmp(token_lst->value, "cd", 2) == 0)
	{
		if (token_lst->next == NULL \
			|| ft_strncmp(token_lst->next->value, "~", 1) == 0)
			path = set_dir("HOME");
		if (access(path, F_OK | X_OK) == 0)
			chdir(path);
		path = getcwd(buf, size);
		ft_putstr_fd("Current directory: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

//__env__
int	builtin_env(t_tokens *token_lst, char *path, char **envp)
{
	if (ft_strncmp(token_lst->value, "env", 3) == 0 && token_lst->next == NULL)
	{
		if (access(path, F_OK | X_OK) == 0)
		{
			print_tab(envp);
		}
		return (0);
	}
	return (1);
}

//__export__
//set export attibuts (= make var available for child processes)
//need to get current process
//duplicate in a tab, set this tab as **envp, add if "export"
//w/out options, export all var + display env token_lst
//free when process ends
//__unset__
//unset + args (= variables)
//substract from export tab
//check when special variable

//__exit__
//end the process
//process then only contain return status
//go to parent or end shell

void	ft_builtins(t_tokens *token_lst, t_group *group, char **envp)
{
	if (ft_strncmp(token_lst->value, "cd", 2) == 0)
		builtin_cd(token_lst, group->cmd[1]);
	else if (ft_strncmp(token_lst->value, "env", 3) == 0)
		builtin_env(token_lst, group->cmd[0], envp);
	else if (ft_strncmp(token_lst->value, "pwd", 3) == 0)
		builtin_pwd(token_lst);
	else if (ft_strncmp(token_lst->value, "echo", 4) == 0)
		builtin_echo(token_lst);
	else
		return ;
}
