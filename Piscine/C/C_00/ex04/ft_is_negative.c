/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 11:48:11 by vspinell          #+#    #+#             */
/*   Updated: 2020/10/28 13:12:18 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int n)
{
	char a;
	char b;

	a = 'N';
	b = 'P';
	if (n >= 0)
	{
		write(1, &b, 1);
	}
	else if (n < 0)
	{
		write(1, &a, 1);
	}
}