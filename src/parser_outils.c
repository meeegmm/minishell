#include "../inc/parsing.h"

int only_spaces(char *str)
{
	// if(!str[0])
	// 	return (1);
	while(*str == ' ')
		str++;
	if(*str == '\0')
		return (1);
	return (0);
}


int    is_built(char *str)
{
    int        i;
    char    *tab[7];

    i = 0;
    tab[0] = "env";
    tab[1] = "pwd";
    tab[2] = "echo";
	tab[3] = "unset";
	tab[4] = "export";
	tab[5] = "cd";
	tab[6] = "exit";
    while (str[i] && i <= 6)
    {
        if (ft_strncmp(str, tab[i], ft_strlen(tab[i])) == 0)
            return (1);
        i++;
    }
    return (0);
}


char **file_access(char **tab)
{
    int i;

    i = 0;
    char **res = malloc(sizeof(char *) * 2);
    if(!res)
        return(NULL); 
    while(tab[i])
    {
        if(access(tab[i], F_OK | R_OK | W_OK ) != 0) //should we remove X_OK ?
        {
            free(res);
            return (NULL);
        }
        i++;
    }
    res[0] = ft_strdup(tab[i - 1]);
    res[1] = NULL;
    return (res);
}

/*int main()
{
    char **tab = malloc(sizeof(char *) * 4);
    tab[0] = "file1";
    tab[1] = "file2";
    tab[2] = "file3";
    tab[3] = NULL;

    char **res = file_access(tab);
    if(res != NULL)
    {
        printf("le vrai output : %s\n", res[0]);
        free_tab(res);
    }
    else
        printf("No access\n");
    free(tab);
    return (0);
}*/