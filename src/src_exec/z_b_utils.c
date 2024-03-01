#include "../../inc/minishell.h"
#include "../../inc/exec.h"
#include "../../inc/parsing.h"

//set_env function
char	*set_dir(char *path)
{

	path = getenv(path);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	return ("error");
}