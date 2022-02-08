/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:04:55 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 11:46:00 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_matrix_add(char ***matrix, char *line_to_add)
{
	int		y;
	char	**tmp;

	y = -1;
	if (!line_to_add)
		return ;
	tmp = malloc(sizeof(char *) * (ft_matrixlen(*matrix) + 2));
	tmp[ft_matrixlen(*matrix) + 1] = NULL;
	while (*matrix && (*matrix)[++y])
	{
		tmp[y] = malloc(sizeof(char) * ft_strlen((*matrix)[y]) + 1);
		ft_memcpy(tmp[y], (*matrix)[y], ft_strlen((*matrix)[y]));
		tmp[y][ft_strlen((*matrix)[y])] = '\0';
	}
	tmp[ft_matrixlen(*matrix)] = malloc(sizeof(char) * \
	ft_strlen(line_to_add) + 1);
	ft_memcpy(tmp[ft_matrixlen(*matrix)], line_to_add, ft_strlen(line_to_add));
	tmp[ft_matrixlen(*matrix)][ft_strlen(line_to_add)] = '\0';
	ft_matrixfree(*matrix);
	(*matrix) = tmp;
}

void	ft_matrixcopy(char ***cp_matrix, char **matrix)
{
	int	y;

	y = -1;
	*cp_matrix = malloc(sizeof(char *) * (ft_matrixlen(matrix) + 1));
	(*cp_matrix)[ft_matrixlen(matrix)] = NULL;
	while (matrix[++y])
	{
		(*cp_matrix)[y] = malloc(sizeof(char) * ft_strlen(matrix[y]) + 1);
		ft_memcpy((*cp_matrix)[y], matrix[y], ft_strlen(matrix[y]));
		(*cp_matrix)[y][ft_strlen(matrix[y])] = '\0';
	}
}

void	ft_matrixprint(char **matrix)
{
	int	y;

	y = -1;
	while (matrix[++y])
		printf("%s\n", matrix[y]);
}

void	ft_matrixfree(char **matrix)
{
	int	y;

	y = -1;
	while (matrix && matrix[++y])
		free(matrix[y]);
	free(matrix);
}
