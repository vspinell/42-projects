/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:54:06 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/22 15:48:58 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((ft_strlen(haystack) + ft_strlen(n) == 0))
		return ((char *)haystack);
	if (ft_strlen(n) > ft_strlen(haystack))
		return (NULL);
	if (ft_strlen(n) == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (n[j] == haystack[i + j] && (i + j) < len)
		{
			if (n[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
