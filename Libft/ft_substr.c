/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:02:06 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/23 16:47:38 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - start > len ? len : ft_strlen(s) - start;
	if (!(substr = (char*)malloc((len + 1) * sizeof(const char))))
		return (NULL);
	while (s[i])
	{
		if ((i >= start && j < len))
		{
			substr[j] = s[i];
			j++;
		}
		i++;
	}
	substr[j] = 0;
	return (substr);
}
