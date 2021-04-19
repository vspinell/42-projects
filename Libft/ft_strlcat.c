/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minzeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:56:49 by minzeo            #+#    #+#             */
/*   Updated: 2021/01/19 19:14:52 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	r;

	i = 0;
	j = 0;
	r = 0;
	while (dst[i])
		i++;
	while (src[r])
		r++;
	if (dstsize <= i)
		r += dstsize;
	else
		r += i;
	while (src[j] && i + 1 < dstsize)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (r);
}
