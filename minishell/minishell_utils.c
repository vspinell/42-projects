/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 12:17:16 by francesco         #+#    #+#             */
/*   Updated: 2021/10/27 11:51:57 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	numbwords(char const *s, char c)
{
	unsigned int	i;
	unsigned int	k;

	i = -1;
	k = 0;
	while (s[++i])
	{
		if (s[i] == '"' && s[i + 1])
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		if (s[i] == 39 && s[i + 1])
		{
			i++;
			while (s[i] && s[i] != 39)
				i++;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			k += 1;
		if (!s[i])
			break ;
	}
	return (k);
}

unsigned int	numbletter(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && s[i + 1])
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		if (s[i] == 39 && s[i + 1])
		{
			i++;
			while (s[i] && s[i] != 39)
				i++;
		}
		if (s[i] == '\0')
			return (i);
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			return (i + 1);
		i++;
	}
	return (i);
}

char	**mallocstring(char **str,
		char const *s, char c, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	nl;

	i = 0;
	j = 0;
	while (i < nb)
	{
		while (s[j] == c)
			j++;
		nl = numbletter(s + j, c);
		str[i] = (char *)malloc(sizeof(char) * (nl + 1));
		k = 0;
		while (k < nl)
		{
			str[i][k] = s[j];
			k++;
			j++;
		}
		str[i][k] = '\0';
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	nb;

	if (!s)
		return (NULL);
	nb = numbwords(s, c);
	str = (char **)malloc(sizeof(char *) * (nb + 1));
	str[nb] = (NULL);
	mallocstring(str, s, c, nb);
	return (str);
}
