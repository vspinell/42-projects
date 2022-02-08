/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minzeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:36:14 by minzeo            #+#    #+#             */
/*   Updated: 2020/11/10 16:26:19 by minzeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int *array;
	int i;
	int j;

	if (min >= max)
	{
		*range = 0;
		return (0);
	}
	i = min;
	j = 0;
	array = malloc((max - min) * sizeof(int) + 1);
	if (array == NULL)
	{
		*range = 0;
		return (-1);
	}
	while (i < max)
	{
		array[j] = i;
		j++;
		i++;
	}
	*range = array;
	return (j);
}
