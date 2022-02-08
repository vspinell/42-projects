/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:20:42 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/03 12:37:39 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_buffupdate(char *buff, int j)
{
	int i;

	i = 0;
	while (buff[j])
		buff[i++] = buff[j++];
	buff[i] = 0;
}

int		ft_newline(char *buff, char **line)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	*line = ft_realloc(line);
	len = ft_strlen(*line);
	while (buff[j] && buff[j] != '\n')
	{
		(*line)[j + len] = buff[j];
		j++;
	}
	(*line)[j + len] = 0;
	if (buff[j] == 0)
	{
		buff[0] = 0;
		return (0);
	}
	j++;
	ft_buffupdate(buff, j);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	static char buff[4096][BUFFER_SIZE + 1];

	if (fd < 0 || !line || buff[fd] <= 0 || fd > 255 || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (!(*line = malloc(BUFFER_SIZE + 1)))
		return (-1);
	ft_bzero(*line, BUFFER_SIZE);
	if (ft_newline(buff[fd], line))
	{
		*line = ft_reallocfin(line);
		return (1);
	}
	while ((i = read(fd, buff[fd], BUFFER_SIZE)) > 0)
	{
		buff[fd][i] = 0;
		if (ft_newline(buff[fd], line))
		{
			*line = ft_reallocfin(line);
			return (1);
		}
	}
	*line = ft_reallocfin(line);
	return (i);
}
