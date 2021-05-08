

#include "push_swap.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	if (!(dst && src))
		return (0);
	if (dstsize != 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strcount(char *str, char c)
{
	size_t	countstr;

	countstr = 0;
	while (*str)
	{
		if (*str != c)
			if (*(str + 1) == c || *(str + 1) == '\0')
				countstr++;
		str++;
	}
	return (countstr);
}

size_t	ft_strclen(char *s, char c)
{
	size_t	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		else
			i++;
	}
	return (i);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	len;
	char	**arr;

	if (!s)
		return (NULL);
	if (!(arr = malloc(sizeof(s) * (ft_strcount(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = ft_strclen(s, c);
			if (!(arr[i] = malloc(len + 1)))
				return (NULL);
			ft_strlcpy(arr[i], s, len + 1);
			s += len;
			i++;
		}
		else
			s++;
	}
	arr[i] = NULL;
	return (arr);
}