/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:40:29 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/27 17:08:54 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_activateflag2(char c, int *d_q, int *s_q)
{
	if ((c == 34 && *s_q == 0) || (c == 34 && *d_q == 1))
	{
		if (*d_q == 0)
		{
			*d_q = 1;
			return (1);
		}
		else
			*d_q = 0;
	}
	else if ((c == 39 && *d_q == 0) || (c == 39 && *s_q == 1))
	{
		if (*s_q == 0)
		{
			*s_q = 1;
			return (1);
		}
		else
			*s_q = 0;
	}
	return (0);
}

int	ft_check_specialcase(char ***cmd)
{
	int	i;
	int	d_q;
	int	s_q;
	int	y;
	int	u;

	u = 0;
	i = 0;
	s_q = 0;
	d_q = 0;
	while (*cmd && (*cmd)[i])
	{
		y = 0;
		while ((*cmd)[i][y])
		{
			if (ft_activateflag2((*cmd)[i][y], &d_q, &s_q))
				u = i;
			y++;
		}
		i++;
	}
	if (s_q == 1 || d_q == 1)
		return (u);
	return (-1);
}

int	ft_isredir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_addstring_to_tmp(int flag, int y, char ***tmp, char *cmd)
{
	char	*str;
	int		len;

	len = 0;
	while (flag == 0 && !ft_isredir(cmd[y]) && cmd[y])
	{
		y++;
		len++;
	}
	while (flag == 1 && (cmd[y] == '>' || cmd[y] == '<') && cmd[y])
	{
		len++;
		y++;
	}
	str = malloc(len + 1);
	ft_memcpy(str, cmd + (y - len), len);
	str[len] = '\0';
	ft_matrix_add(tmp, str);
	free(str);
	return (y);
}

char	**ft_special_realloc(char **cmd)
{
	char	**tmp;
	int		i;
	int		y;

	i = 0;
	tmp = NULL;
	while (cmd[i])
	{
		if (ft_countredir(cmd[i]) != ft_strlen(cmd[i]))
		{
			y = 0;
			while (cmd[i][y])
			{
				if (!ft_isredir(cmd[i][y]))
					y = ft_addstring_to_tmp(0, y, &tmp, cmd[i]);
				else
					y = ft_addstring_to_tmp(1, y, &tmp, cmd[i]);
			}
		}
		else
			ft_matrix_add(&tmp, cmd[i]);
		i++;
	}
	ft_matrixfree(cmd);
	return (tmp);
}
