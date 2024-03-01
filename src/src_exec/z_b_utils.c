#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"

//set_env function
char	*set_env(char *env)
{
	char	*envp;

	envp = getenv(env);
	if (access(env, F_OK | X_OK) == 0)
		return (env);
	return ("error");
}