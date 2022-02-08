/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:15:51 by vspinell          #+#    #+#             */
/*   Updated: 2020/11/05 19:15:59 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char *p;

	p = dest;
	while (*p != '\0')
		p++;
	while (*src != '\0' && nb > 0)
	{
		*p = *src;
		p++;
		src++;
		nb--;
	}
	*p = '\0';
	return (dest);
}
