/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:46:41 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/11 15:46:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

char	*ft_strchr(const char *s, int c)
{
	while ((*s != (unsigned char)c) && (*s != '\0'))
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
