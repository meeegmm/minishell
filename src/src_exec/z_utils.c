#include "../../inc/exec.h"

// ___LIBFT PIPEX___

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*sub(const char *s, unsigned int start, size_t len, char *dest)
{
	unsigned int	i;

	i = 0;
	while (s && s[start])
	{
		if (i < len)
		{
			dest[i] = s[start];
			i++;
		}
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, int start, int len)
{
	size_t		i;
	char		*dest;

	i = 0;
	if (!s)
		return (NULL);
	if (s && start > ft_strlen(s))
	{
		dest = malloc(1 * sizeof(char));
		if (!dest)
			return (NULL);
		dest[i] = '\0';
		return (dest);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	sub(s, start, len, dest);
	return (dest);
}

static int	token_count(char *str, char c)
{
	int	i;
	int	token;

	i = 0;
	token = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			token++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (token);
}

static int	token_size(char *str, char c, int i)
{
	int	size;

	size = 0;
	while (str && str[i] && str[i] != c)
	{
		if (str[i] != c)
			size++;
		i++;
	}
	return (size);
}

static char	*split_substr(char *str, size_t start, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	split_free(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

char	**ft_split(char *s, char c)
{
	int				i;
	int				j;
	int				token;
	char			**str;
	int				size;

	i = 0;
	j = -1;
	token = token_count(s, c);
	str = (char **)malloc((token + 1) * sizeof(char *));
	if (!s || !str)
		return (split_free(str, j), NULL);
	while (++j < token)
	{
		while (s && s[i] == c)
			i++;
		size = token_size(s, c, i);
		str[j] = split_substr(s, i, size);
		if (!str[j])
			split_free(str, j);
		i += size;
	}
	str[j] = 0;
	return (str);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
