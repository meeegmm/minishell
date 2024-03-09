#include "../../inc/exec.h"

//TODO: assign good exit status if fail
//		choose a function for error messages to write on good fd
//		put cmd when error
//		add checks
//		
//		handle args
//		1 struct by builtin?
//		pass by tmp for each?
//		error returns: format = 2 / path = 3 / fail = 4

//__echo__
//remove "" at display
int	builtin_echo(t_tokens *token_lst)
{
	int		option;
	char	*cmd;

	option = 0;
	cmd = token_lst->value;
	if (ft_strncmp(token_lst->value, "echo", 4) == 0)
	{
		if (get_tokens_nb(token_lst) < 2)
		{
			printf("\n");
			return (0);
		}
		token_lst = token_lst->next;
		if (ft_strncmp(token_lst->value, "-n", 2) == 0)
		{
			option = 1;
			token_lst = token_lst->next;
		}
		// else
		// 	token_lst = token_lst->next;
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
	else
		ft_putstr_fd(cmd, ": Command failed\n", 2);
	return (4);
}

// __pwd__
int	builtin_pwd(t_tokens *token_lst)
{

	char	*cmd;
	size_t	size;
	char	*buf;
	char	*dir;

	size = 2048; //look for optimal value
	buf = malloc(sizeof(char) * (size + 1));
	cmd = token_lst->value;
	if (!buf)
		return (1);
	if (get_tokens_nb(token_lst) > 1)
	{
		ft_putstr_fd(cmd, ": Invalid format: Too many arguments\n", 2);
		return (2);
	}
	if (ft_strncmp(token_lst->value, "pwd", 3) == 0)
	{
		dir = getcwd(buf, size);
		printf("%s", dir);
		printf("\n");
		free(buf);
		return (0);
	}
	free(buf);
	ft_putstr_fd(cmd, ": Command failed\n", 2);
	return (4);
}

//__cd__
// change $OLDPWD
int	builtin_cd(t_tokens *token_lst, char *path)
{
	char	*cmd;

	cmd = token_lst->value;
	if (get_tokens_nb(token_lst) > 2)
	{
		ft_putstr_fd(cmd, ": Invalid format: Too many arguments\n", 2);
		return (2);
	}
	if (ft_strncmp(token_lst->value, "cd", 2) == 0)
	{
		if (token_lst->next == NULL \
			|| ft_strncmp(token_lst->next->value, "~", 1) == 0)
			path = set_dir("HOME");
		else if (ft_strncmp(token_lst->next->value, "-", 1) == 0)
		{
			path = set_dir("OLDPWD");
			printf("%s\n", path);
		}
		if (access(path, F_OK | X_OK) == 0)
			chdir(path);
		else
		{
			ft_putstr_fd(cmd, ": Invalid path\n", 2);
			return (3);
		}
		return (0);
	}
	ft_putstr_fd(cmd, ": Command failed\n", 2);
	return (4);
}

//__env__
int	builtin_env(t_tokens *token_lst, char **envp)
{
	char	*cmd;

	cmd = token_lst->value;
	if (get_tokens_nb(token_lst) > 1)
	{
		ft_putstr_fd(cmd, ": Invalid format: Too many arguments\n", 2);
		return (2);
	}
	if (ft_strncmp(token_lst->value, "env", 3) == 0)
	{
		print_tab(envp);
		return (0);
	}
	else
		ft_putstr_fd(cmd, ": Command failed\n", 2);
	return (4);
}

//__export__
//set export attributs (= make var available for child processes)
//need to get current process
//duplicate in a tab, set this tab as **envp, add if "export"
//w/out options, export all var + display env token_lst
//free when process ends
//__unset__
//unset + args (= variables)
//substract from export tab
//check when special variable
// int	builtin_export(t_tokens *token_lst, char **envp)
// {
// 	char	*cmd;

// 	cmd = token_lst->value;
// 	if (ft_strncmp(token_lst->value, "export", 6) == 0)
// 	{
// 		if (get_tokens_nb(token_lst) == 1)
// 		{
// 			print_tab(envp);
// 			return (0);
// 		}
// 	}
// 	else
// 		ft_putstr_fd(cmd, ": Command failed\n", 2);
// 	return (4);
// }

//__exit__
//end the process
//process then only contain return status
//go to parent or end shell

void	ft_builtins(t_tokens *token_lst, t_group *group, char **envp)
{
	if (ft_strncmp(token_lst->value, "cd", 2) == 0)
		builtin_cd(token_lst, group->cmd[1]);
	else if (ft_strncmp(token_lst->value, "env", 3) == 0)
		builtin_env(token_lst, envp);
	else if (ft_strncmp(token_lst->value, "pwd", 3) == 0)
		builtin_pwd(token_lst);
	else if (ft_strncmp(token_lst->value, "echo", 4) == 0)
		builtin_echo(token_lst);
	else
		return ;
}
