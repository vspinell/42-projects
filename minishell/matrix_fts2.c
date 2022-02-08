/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_fts2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:45:37 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 11:46:02 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_matrix_remove_w2(t_term *term, char *rebuild, char del)
{
	int	i;

	i = -1;
	while (term->info.env_copy[++i])
	{
		if (!ft_strncmp(rebuild, term->info.env_copy[i], ft_strlen(rebuild)) \
		&& (term->info.env_copy[i][ft_strlen(rebuild)] == del || \
		term->info.env_copy[i][ft_strlen(rebuild)] == '\0'))
		{
			ft_matrix_remove(&term->info.env_copy, term->info.env_copy[i]);
			break ;
		}
	}
}

void	ft_matrix_remove_w(t_term *term, char *cmd, char del, int no_del)
{
	int		i;
	char	*rebuild;

	rebuild = NULL;
	if (!cmd)
		return ;
	i = ft_strchr(cmd, del);
	if (no_del == 1)
		i = ft_strlen(cmd);
	if (i > 0 && ft_isprint(cmd[i - 1]))
	{
		rebuild = malloc(sizeof(char) * (i + 1));
		ft_memcpy(rebuild, cmd, i);
		rebuild[i] = '\0';
		ft_matrix_remove_w2(term, rebuild, del);
		free(rebuild);
	}
}

int	ft_matrix_find_i_line(char **matrix, char *line_to_find)
{
	int		i;

	i = 0;
	while (matrix && matrix[i])
	{
		if ((!ft_strncmp(line_to_find, matrix[i], ft_strlen(line_to_find))) \
		&& (matrix[i][ft_strlen(line_to_find)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_matrix_remove2(char ***matrix, char ***tmp, int rem_line)
{
	int	y;
	int	i;

	y = -1;
	i = 0;
	while (*matrix && (*matrix)[++y])
	{
		if (y == rem_line)
			continue ;
		(*tmp)[i] = malloc(sizeof(char) * ft_strlen((*matrix)[y]) + 1);
		ft_memcpy((*tmp)[i], (*matrix)[y], ft_strlen((*matrix)[y]));
		(*tmp)[i][ft_strlen((*matrix)[y])] = '\0';
		i++;
	}	
}

void	ft_matrix_remove(char ***matrix, char *line_to_rem)
{
	int		rem_line;
	char	**tmp;

	tmp = NULL;
	if (!*matrix && !line_to_rem)
		return ;
	rem_line = ft_matrix_find_i_line(*matrix, line_to_rem);
	if (rem_line != -1)
	{
		tmp = malloc(sizeof(char *) * ft_matrixlen(*matrix));
		tmp[ft_matrixlen(*matrix) - 1] = NULL;
		ft_matrix_remove2(matrix, &tmp, rem_line);
		ft_matrixfree(*matrix);
		(*matrix) = tmp;
	}
}
