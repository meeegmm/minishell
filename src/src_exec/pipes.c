#include "../../inc/exec.h"

//will get structure between each pipe

// int	cmds_nb(char *line)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (line[i])
// 	{
// 		while (line[i] && (line[i] == ' '))
// 			i++;
// 		if (line[i])
// 			count++;
// 		while (line[i] && (line[i] != '|'))
// 			i++;
// 		if (line[i] == '|')
// 			i++;
// 	}
// 	return (count);
// }

// char	**split_cmds(char *line)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**cmds;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	cmds = malloc(sizeof (char *) * (cmds_nb(line) + 1));
// 	while (line[i])
// 	{
// 		j = i;
// 		while (line[i] && (line[i] != '|'))
// 			i++;
// 		if (i > j)
// 		{
// 			cmds[k] = malloc(sizeof(char) * ((i - j) + 1));
// 			ft_strncpy(cmds[k], &line[j], i - j);
// 			k++;
// 		}
// 		while (line[i] == '|' || line[i] == ' ')
// 			i++;
// 	}
// 	cmds[k] = NULL;
// 	return (cmds);
// }
