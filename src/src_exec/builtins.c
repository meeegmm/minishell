#include "../../inc/exec.h"

//$PWD au lancement + SHLVL (> 1000 ou != nb  == 0)

//TODO: assign good exit status if fail
//		choose a function for error messages to write on good fd
//		add checks: think about quotes
//		handle args
//		1 struct for builtin?
//		pass by tmp for each?
//		error function (define values in .h)
//		error returns: format = 2 / path = 3 / fail = 4
//		join env + export + unset?

//__echo__
//invalid read when space after ""
//function is_option?
int	builtin_echo(t_group *group)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (ft_strncmp(group->cmd[0], "echo", 4) == 0)
	{
		if (tab_size(group->cmd) < 2)
		{
			printf("\n");
			return (0);
		}
		i++;
		while (group->cmd[i])
		{
			if (ft_strncmp(group->cmd[i], "-n", 2) == 0 \
											&& is_char(group->cmd[i], 'n'))
			{
				option = 1;
				i++;
			}
			else
				break ;
		}
		while (group->cmd[i])
		{
			printf("%s", group->cmd[i]);
			if (group->cmd[i + 1] != NULL)
				printf(" ");
			i++;
		}
		if (!option)
			printf("\n");
		return (0);
	}
	else
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

// __pwd__
int	builtin_pwd(t_group *group)
{
	size_t	size;
	char	*buf;
	char	*dir;

	size = 2048; /* look for optimal value */
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (1);
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strncmp(group->cmd[1], "-", 1) == 0 \
								&& !is_char(group->cmd[1], '-'))
		{
			ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
			//invalid option
			return (2);
		}
	}
	if (ft_strncmp(group->cmd[0], "pwd", 3) == 0)
	{
		dir = getcwd(buf, size);
		printf("%s", dir);
		printf("\n");
		free(buf);
		return (0);
	}
	free(buf);
	ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

//__cd__
// change $OLDPWD
int	builtin_cd(t_group *group, char *path, t_list_env *env_lst)
{
	// mod_var(env_lst, "PWD", set_dir(env_lst, path));
	if (tab_size(group->cmd) > 2)
	{
		ft_putstr_fd("minishell", group->cmd[0], 2);
		//too many arguments
		return (2);
	}
	if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
	{
		if (tab_size(group->cmd) == 1 \
			|| ft_strncmp(group->cmd[1], "~", 1) == 0)
			path = set_dir(env_lst, "HOME");
		else if (ft_strncmp(group->cmd[1], "-", 1) == 0)
		{
			path = set_dir(env_lst, "OLDPWD");
			printf("%s\n", path);
		}
		if (chdir(path) == -1)
		{
			ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
			perror(NULL);
			return (3);
		}
		return (0);
	}
	ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

//__env__
int	builtin_env(t_group *group, t_list_env *env_lst)
{
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strcmp(group->cmd[1], "env") != 0)
		{
			if (access(group->cmd[1], F_OK | X_OK) == -1)
			{
				ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
				perror(NULL);
				return (3);
			}
		}
	}
	if (ft_strncmp(group->cmd[0], "env", 3) == 0)
	{
		print_env_list(env_lst);
		return (0);
	}
	else
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

//__export__
//exported env in .h?
//can modify variable value
//set export attributs (= make var available for child processes)
//need to get current process
//duplicate in a tab, set this tab as **envp, add if "export"
//free when process ends
int	builtin_export(t_group *group, t_list_env *env_lst)
{
	if (ft_strncmp(group->cmd[0], "export", 3) == 0)
	{
		if (tab_size(group->cmd) == 1)
		{
			while (env_lst != NULL)
			{
				printf("declare -x %s=\"%s\"\n", env_lst->key, env_lst->value);
				env_lst = env_lst->next;
			}
			return (0);
		}
		// else
		// {
			
		// }
	}
	else
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

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

void	ft_builtins(t_group *group, t_list_env *env_lst)
{
	if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
		builtin_cd(group, group->cmd[1], env_lst);
	else if (ft_strncmp(group->cmd[0], "env", 3) == 0)
		builtin_env(group, env_lst);
	else if (ft_strncmp(group->cmd[0], "pwd", 3) == 0)
		builtin_pwd(group);
	else if (ft_strncmp(group->cmd[0], "echo", 4) == 0)
		builtin_echo(group);
	else if (ft_strncmp(group->cmd[0], "export", 6) == 0)
		builtin_export(group, env_lst);
	else
		return ;
}
