/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_computlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:21:37 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 13:59:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_intlen(size_t n, int base)
{
	int i;

	i = (n == 0) ? 1 : 0;
	while (n > 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_utoa(size_t n, int base, int len)
{
	char	*dec;
	char	*exa;
	char	*conv;
	int		index;
	char	*p;

	exa = "0123456789abcdef";
	dec = "0123456789";
	p = (base == 10) ? dec : exa;
	if (!(conv = malloc(len + 1)))
		return (0);
	conv[len] = 0;
	while (len)
	{
		index = n % base;
		conv[--len] = p[index];
		n /= base;
	}
	return (conv);
}
