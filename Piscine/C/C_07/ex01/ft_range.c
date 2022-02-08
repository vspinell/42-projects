/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:11:33 by vspinell          #+#    #+#             */
/*   Updated: 2020/11/11 17:39:09 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int *p;
	int range;
	int index;

	range = max - min;
	index = 0;
	if ((!(p = malloc(range * sizeof(int)))))
		return (NULL);
	if (min >= max)
		return (NULL);
	while (min < max)
	{
		p[index] = min;
		index++;
		min++;
	}
	return (p);
}
