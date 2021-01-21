/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:40:49 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/19 12:48:03 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_checkchar(const char c, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	j = 0;
	while (ft_checkchar(s1[start], set))
		start++;
	j = 0;
	while (ft_checkchar(s1[end], set) && end > start)
		end--;
	if (!(str = (char*)malloc((end - start + 2) * sizeof(char))))
		return (NULL);
	while ((start + j) != (end + 1))
	{
		str[j] = s1[start + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
