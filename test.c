#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int quotes_ok(char *str) //plus court
{
	int i;
	int res;

	i = 0;
	res = 1;
	while(str[i])
	{
		if(str[i] == '"')
		{
			res = 0;
			while(str[i])
			{
				i++;
				if(str[i] == '"')
				{
					res = 1;
					break;
				}
			}
		}
		else if(str[i] == 39)
		{
			res = 0;
			while(str[i])
			{
				i++;
				if(str[i] == 39)
				{
					res = 1;
					break;
				}
			}
		}
		i++;
	}
	return (res);
}

int main(int ac, char **av)
{
    (void)ac;
    printf("%d\n", quotes_ok(av[1]));
    return 0;
}