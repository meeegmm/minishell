#include "../../inc/exec.h"

//env when env -i
t_list_env	*env_lst_sos(void)
{
	char		*buf;
	size_t		size;
	t_list_env	*env_lst;

	buf = NULL;
	size = 0;
	env_lst = malloc(sizeof(t_list_env));
	if (!env_lst)
		return (NULL);
	env_lst->key = "PWD";
	env_lst->value = getcwd(buf, size);
	env_lst->next = malloc(sizeof(t_list_env));
	if (!env_lst->next)
		return (NULL);
	env_lst->next->key = "SHLVL";
	env_lst->next->value = "1";
	env_lst->next->next = NULL;
	free(buf);
	return (env_lst);
}

//env for pgm
char	**set_envp(char **envp)
{
	t_list_env	*env_lst;
	char		**new_envp;

	if (*envp == NULL)
		env_lst = env_lst_sos();
	else
		env_lst = get_list(envp);
	new_envp = get_envp(env_lst);
	// free_envp_list(env_lst);
	return (new_envp);
}

//return var or end of list if !var
t_list_env	*check_var(t_list_env *env_lst, char *var)
{
	while (env_lst->next != NULL)
	{
		if (ft_strncmp(env_lst->next->key, var, ft_strlen(var)) == 0)
			return (env_lst);
		else
			env_lst = env_lst->next;
	}
	return (env_lst);
}

//modify or add var
void	mod_var(t_list_env **env_lst, char *key, char *value)
{
	if (!(*env_lst)->next)
	{
		ft_lstadd_back(env_lst, (*env_lst)->next);
		(*env_lst)->key = ft_strdup(key);
		(*env_lst)->value = ft_strdup(value);
		(*env_lst)->next = NULL;
	}
	else
	{
		free((*env_lst)->value);
		(*env_lst)->value = ft_strdup(value);
	}
}


void	remove_var(t_list_env *env_lst)
{
	if (!env_lst->next)
	{
		free(env_lst->key);
		free(env_lst->value);
		env_lst = NULL;
	}
	else
	{
		free(env_lst->next->key);
		free(env_lst->next->value);
		env_lst->next = env_lst->next->next;
	}
}
