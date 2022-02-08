/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:04:56 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/02 18:41:07 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_realloc(char **line)
{
	int		i;
	char	*tmp;

	if (!*line)
		return (0);
	i = 0;
	if (!(tmp = malloc(ft_strlen(*line) + BUFFER_SIZE + 1)))
		return (0);
	while ((*line)[i])
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i] = 0;
	free(*line);
	return (tmp);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)(s++) = 0;
}

char	*ft_reallocfin(char **line)
{
	int		i;
	char	*tmp;

	if (!*line)
		return (0);
	i = 0;
	if (!(tmp = malloc(ft_strlen(*line) + 1)))
		return (0);
	while ((*line)[i])
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i] = 0;
	free(*line);
	return (tmp);
}
