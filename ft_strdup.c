/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 11:06:02 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/17 13:32:38 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	char	*t;

	i = ft_strlen(s1) + 1;
	if (!(str = (char*)malloc(i * sizeof(char))))
		return (0);
	t = str;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	*str = '\0';
	return (t);
}
