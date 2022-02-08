/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:55:19 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 12:15:58 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + 1));
	tmp = ptr;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (tmp);
}

int	ft_isprint(int c)
{
	if (c > 32 && c <= 126)
		return (1);
	else
		return (0);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strchr_mod(const char *s, int c, int skip)
{
	int	i;
	int	n_times;

	n_times = 0;
	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			if (n_times == skip)
				return (i);
			n_times++;
		}
		i++;
	}
	return (-1);
}
