/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_libft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:40 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/25 13:23:49 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	ft_strlen(const char *s)
{
	int	i;

	if(!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*s;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s = (char *)malloc(sizeof(*s1) * (len + 1));
	if (s == NULL)
		return (NULL);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int res;

	i = 0;
	res = 0;
	while (s1[i] && s2[i])
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if(!s1[i] && s2[i])
		res = s2[i] * (-1);
	else if(s1[i] && (!s2[i]))
		res = s1[i];
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	res = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	c1;
	size_t	i;

	c1 = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c1)
			return ((char*)(s + i));
		i++;
	}
	if (s[i] == c1)
		return ((char*)(s + i));
	return (NULL);
}