#include "../../inc/exec.h"

//TODO: assign good exit status if fail
//		choose a function for error messages to write on good fd
//		add checks: think about quotes
//		handle args
//		1 struct for builtin?
//		error returns: format = 2 / path = 3 / fail = 4

//__echo__
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
			write(1, "\n", 1);
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
		//write on exec->fd_out?
		while (group->cmd[i])
		{
			ft_putstr(group->cmd[i]);
			if (group->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (!option)
			write(1, "\n", 1);
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

	size = 0;
	buf = NULL;
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
		ft_putstr(dir);
		write(1, "\n", 1);
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
			path = set_path(env_lst, "HOME");
		else if (ft_strncmp(group->cmd[1], "-", 1) == 0)
		{
			path = set_path(env_lst, "OLDPWD");
			ft_putstr(path);
			write(1, "\n", 1);
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
			ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
			write(2, "Too many arguments\n", 19);
			return (3);
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
int	builtin_export(t_group *group, t_list_env *env_lst)
{
	int			i;
	t_list_env	*tmp;

	i = 1;
	tmp = env_lst;
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
		else
		{
			while (group->cmd[i])
			{
				printf("key = %s\n", env_lst->key);
				printf("\n\n\n");
				if (ft_strncmp(env_lst->key, get_key(group->cmd[i]), \
												ft_strlen(env_lst->key) != 0))
					env_lst = check_var(&env_lst, group->cmd[i]);
				printf("key = %s\n", env_lst->key);
				printf("\n\n\n");
				mod_var(&env_lst, group->cmd[i]);
				env_lst = tmp;
				i++;
			}
		}
		return (0);
	}
	else
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

//__unset__
//voir pour le prmier node
//okay dans la fonction mais modifeir **env_lst pour aller au next
int	builtin_unset(t_group *group, t_list_env *env_lst)
{
	int	i;
	t_list_env	*tmp;

	i = 1;
	tmp = env_lst;
	if (ft_strncmp(group->cmd[0], "unset", 5) == 0)
	{
		if (tab_size(group->cmd) == 1)
			return (0);
		else
		{
			while (group->cmd[i])
			{
				if (ft_strncmp(env_lst->key, get_key(group->cmd[i]), \
												ft_strlen(group->cmd[i])) != 0)
				{
					env_lst = check_var(&env_lst, group->cmd[i]);
					remove_var(&env_lst);
				}
				else
				{
					remove_first(&env_lst);
					tmp = env_lst;
				}
				env_lst = tmp;
				printf("\n\n");
				print_env_list(env_lst);
				i++;
			}
		}
		return (0);
	}
	else
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
	return (4);
}

//__exit__
//end the process
//process then only contain return status
//go to parent or end shell
