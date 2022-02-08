/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:00:30 by vspinell          #+#    #+#             */
/*   Updated: 2020/10/28 19:42:19 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int index;
	int index2;
	int c;

	index = 0;
	while (index < size)
	{
		index2 = index + 1;
		while (index2 < size)
		{
			if (tab[index] > tab[index2])
			{
				c = tab[index];
				tab[index] = tab[index2];
				tab[index2] = c;
			}
			index2++;
		}
		index++;
	}
}
