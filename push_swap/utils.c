/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:25:09 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/19 12:25:12 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_realloc(char *line, char c)
{
	char	*newl;
	int		i;

	newl = 0;
	i = 0;
	newl = malloc(ft_strlen(line) + 2);
	if (!newl)
		return (0);
	while (line && line[i])
	{
		newl[i] = line[i];
		i++;
	}
	newl[i++] = c;
	newl[i] = 0;
	free(line);
	return (newl);
}

int	get_next_line(char **line)
{
	int		ret;
	char	buff;

	ret = 0;
	if (!line)
		return (ret);
	*line = malloc(1);
	if (!line)
		return (-1);
	(*line)[0] = 0;
	while (1)
	{
		ret = read(0, &buff, 1);
		if (ret == 0)
			break ;
		if (buff != '\n')
			*line = ft_realloc(*line, buff);
		else
			return (1);
	}
	if (ret == -1)
	{
		free(*line);
		*line = 0;
	}
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_check_doubles(t_data *head)
{
	t_data	*browse;
	t_data	*jump;

	if (head == 0)
		return ;
	jump = head;
	while (jump->next)
	{
		browse = jump;
		while (browse->next)
		{
			if (jump->num == browse->next->num)
			{
				write(1, "Error\n", 6);
				exit(EXIT_FAILURE);
			}
			browse = browse->next;
		}
		jump = jump->next;
	}
}
