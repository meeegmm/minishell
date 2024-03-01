#include "../../inc/exec.h"

//TODO: assign good exit status if fail
//		choose a function for error messages to write on good fd
//		one builtins function for all w/ checks and free
//		handle if env or path is unset
//		pass by tmp for each?


//__echo__Use print_list w/out first node?
//output the args, separated ' ' end by /n witout -n
int	built_echo(t_group *group)
{
	int	i;

	i = 1;
	if (ft_strncmp(group->cmd[0], "/bin/echo", ft_strlen(group->cmd[0]))  == 0)
	{
		if (ft_strncmp(group->cmd[1], "-n", 2) == 0)
				i = 2;
		while (group->cmd[i] != NULL)
		{
			ft_putstr_fd(group->cmd[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
		if (ft_strncmp(group->cmd[1], "-n", 2) != 0)
			ft_putstr_fd("\n", 1);
		return (0);
	}
	return (-1);
}

// __pwd__Use char *getcwd(char *buf, size_t size)
//display current directory
int	built_pwd(char *cmd)
{
	char	*path;
	char	*buf;
	size_t	size;

	size = 1024; //look for max or string size?
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (-2);
	if (ft_strncmp(cmd, "/bin/pwd", ft_strlen(cmd))  == 0)
	{
		path = getcwd(buf, size);
		free(buf);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (-1);
}


//__cd__Use chdir(path)
int	built_cd(char *cmd, char *path)
{
	char	*buf;
	size_t	size;

	size = 1024; //look for optimal value
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (-2);
	if (ft_strncmp(cmd, "/usr/bin/cd", ft_strlen(cmd)) == 0)
	{
		if (!path || ft_strncmp(path, "~", 1) == 0)
			path = set_home(path);
		if (access(path, F_OK | X_OK) == 0)
		{
			chdir(path);
			if (ft_strncmp(path, ".", 1) == 0)
			{
				path = getcwd(buf, size);
				free(buf);
			}
			ft_putstr_fd("Current directory: ", 1);			
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	return (-1); 
}

//__env__
//
// int	built_env(t_list_env *list, char *cmd)
// {
// 	char	**envp;
//
// 	envp = get_tab(list);
// 	if (ft_strncmp(cmd, "/usr/bin/env", ft_strlen(cmd)) == 0)
// 	{
// 		if (access(envp, F_OK | X_OK) == 0)
// 		{
// 			print_tab(envp);
//			free(tab);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }