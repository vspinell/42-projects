/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:52:26 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/16 15:19:37 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < len)
	{
		if (dst <= src)
			*(char *)(dst + i) = *(char *)(src + i);
		else
			*(char*)(dst + (len - i - 1)) = *(char*)(src + (len - i - 1));
		i++;
	}
	return (dst);
}
