/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:15:19 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 12:16:01 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countquotes(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 34)
			count++;
		i++;
	}
	return (count);
}

int	ft_perror(char *str)
{
	printf("%s\n", str);
	return (-1);
}

int	ft_matrixlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 9 || str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}
