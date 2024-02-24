#include "../../inc/exec.h"

int exec(t_logic_groupe *lg, t_exec *p)
{
	static const char *reserved[] = {"pwd", "export", "env", NULL}; //нужно ли хранить это здесь?

	int i = 0;
	char *cmd_w_path;
	char **new_envp;

	new_envp = get_tab(p->envp_list);
	
	while(reserved[i])
	{
		if (ft_strncmp(lg->cmd[0], (char*)reserved[i], ft_strlen(lg->cmd[0])) == 0)
		{
			printf("Мы нашли builtin\n"); //почему выводит этот результат даже для lg->cmd[0] = "" ?
			ft_env(p);
			free_tab(new_envp);
			break;
		}
		i++;
	}
	if(reserved[i] == NULL)
	{
		cmd_w_path = cmd_check(lg->cmd, new_envp); //вызвать раньше
		if(cmd_w_path == NULL)
		{
			printf("cmd не распознано\n");
			free_tab(new_envp);
			exit(EXIT_FAILURE);
		}
		execve(cmd_w_path, lg->cmd, new_envp);
	}
	return (0);
}