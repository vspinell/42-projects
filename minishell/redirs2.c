/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:11:27 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/27 19:04:45 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_char(char *str, int pos)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	tmp = malloc(ft_strlen(str));
	while (str && str[i])
	{
		if (i != pos)
			tmp[y++] = str[i];
		i++;
	}
	tmp[y] = '\0';
	free(str);
	return (tmp);
}

void	ft_activeflag(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
}

int	ft_quoteclean_routine(char **cmd, int *flag, int flag2, int y)
{
	int	type2;
	int	quote_type;

	quote_type = 0;
	if ((*cmd)[y] == 34)
	{
		quote_type = 34;
		type2 = 39;
	}
	else if ((*cmd)[y] == 39)
	{
		quote_type = 39;
		type2 = 34;
	}
	if (((*cmd)[y] == quote_type && flag2 == 0)
		|| ((*cmd)[y] == quote_type && *flag == 1))
	{
		ft_activeflag(flag);
		(*cmd) = ft_remove_char((*cmd), y);
		if (!(*cmd)[y])
			return (1);
		if ((*cmd)[y] == quote_type || (*cmd)[y] == type2)
			return (2);
	}
	return (0);
}

void	ft_quoteclean(char ***cmd)
{
	int	i;
	int	q[2];
	int	y;
	int	ret;

	i = -1;
	q[0] = 0;
	q[1] = 0;
	while (*cmd && (*cmd)[++i])
	{
		ret = 0;
		y = 0;
		while ((*cmd)[i][y])
		{
			if ((*cmd)[i][y] == 34)
				ret = ft_quoteclean_routine(&(*cmd)[i], &q[0], q[1], y);
			else if ((*cmd)[i][y] == 39)
				ret = ft_quoteclean_routine(&(*cmd)[i], &q[1], q[0], y);
			if (ret == 1)
				break ;
			else if (ret == 2)
				continue ;
			y++;
		}
	}
}
