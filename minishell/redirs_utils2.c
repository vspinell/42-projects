/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:15:41 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/28 16:12:00 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nredir_count(char *line, char *c)
{
	int	n1;
	int	n2;
	int	i;

	n1 = 0;
	n2 = 0;
	i = -1;
	while (line && line[++i])
	{
		if (line[i] == c[0])
		{
			if (ft_strlen(c) == 1)
			{
				if (line[i + 1] != c[0])
					n1++;
				else
					i++;
			}
			else if (line[i + 1] == c[1])
				n2++;
		}
	}
	if (ft_strlen(c) == 1)
		return (n1);
	return (n2);
}

int	ft_sub_checkredirline(char *str, int i, int count)
{
	if (str[i] == 60)
	{
		if (count > 2 || str[i + 1] == 62)
			return (ft_perror("SuPerBasH: syntax error, redirections"));
		count++;
		i++;
	}
	if (str[i] == 62)
	{
		if (count > 2 || str[i + 1] == 60)
			return (ft_perror("SuPerBasH: syntax error, redirections"));
		i++;
		count++;
	}
	return (count);
}

int	ft_checkredirline(t_term *term)
{
	int		i;
	int		count;
	char	*str;

	str = term->prompt;
	i = 0;
	count = 0;
	if (ft_isredir(str[ft_strlen(str) - 1]))
		return (ft_perror("SuPerBasH: parse error near '\\n'"));
	while (str && str[i])
	{
		count = ft_sub_checkredirline(str, i, count);
		if (str[i] != ' ' && str[i] != 62 && str[i] != 60)
			count = 0;
		if (count == -1)
			return (-1);
		if (count > 1 && (str[i + 1] == 60 || str[i + 1] == 62))
			return (ft_perror("SuPerBasH: syntax error, redirections"));
		i++;
	}
	return (0);
}

void	ft_clearpath(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			str = ft_remove_char(str, i);
			continue ;
		}
		if (!str[i])
			break ;
		i++;
	}
}

int	ft_notfound(char *str)
{
	printf("SuPerBash: %s: No such file or directory\n", str);
	return (-1);
}
