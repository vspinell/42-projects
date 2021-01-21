/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:14:41 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/20 16:30:15 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cuntstr(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
		else
		{
			while (s[i] == c && s[i])
				i++;
		}
	}
	return (count);
}

size_t	ft_lenmall(char const *s, char c)
{
	size_t len;

	len = 0;
	while (*s != c && *s)
	{
		s++;
		len++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t			i;
	char			**matrix;
	size_t			len;
	unsigned int	start;

	i = 0;
	len = 0;
	start = 0;
	if (!s)
		return (0);
	if (!(matrix = (char**)malloc((ft_cuntstr(s, c) + 1) * sizeof(char*))))
		return (0);
	while (s[start])
	{
		while (s[start] == c)
			start++;
		len = ft_lenmall(s + start, c);
		matrix[i] = ft_substr(s, start, len);
		i++;
		start += len;
	}
	matrix[ft_cuntstr(s, c)] = 0;
	return (matrix);
}
