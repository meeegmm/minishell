int quotes_ok(char *str) //faire plus court
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