#include "../../inc/exec.h"

//какое поведение в случае, если PWD не найден?

int ft_pwd(t_list_env *list)
{
	char *path;
	char *buf;
	size_t size;

	size = 1024; //какой размер лучше выделить? не стоит ли выделять его динамически?
	buf = malloc(sizeof(char) * (size + 1));
	if(!buf)
		exit(EXIT_FAILURE);
	path = getcwd(buf, size);

	while(list != 0)
	{
		if(ft_strncmp(list->key, "PWD", 3) == 0)
		{
			free(list->value);
			list->value = ft_strdup(path);
			break;
		}
		list = list->next;
	}
	// if(!list)
	// {
	// 	perror("PWD не найдена\n");
	// 	return (1);
	// }
	printf("%s\n", list->value);
	free(buf);
	return 0;
}