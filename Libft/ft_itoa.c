/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:50:13 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/22 19:01:17 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count(int n)
{
	size_t c;

	c = 0;
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char		*ft_itoa(int n)
{
	char	*strn;
	size_t	len;
	size_t	temp;

	if (n <= -2147483648)
		return (ft_strdup("-2147483648"));
	len = n > 0 ? ft_count(n) : ft_count(n) + 1;
	n = n > 0 ? n : -n;
	temp = n;
	if (!(strn = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	strn[len] = '\0';
	if (n == 0)
		strn[len - 1] = 48;
	while (n > 0)
	{
		strn[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
	}
	if (--len == 0 && temp != 0)
		strn[len] = '-';
	return (strn);
}
