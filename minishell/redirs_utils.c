/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:10:29 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/28 15:24:39 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_nredir_count(int x, char **cmd, char *c)
{
	int	count;

	count = 0;
	while (cmd && cmd[x])
	{
		if (ft_nredir_count(cmd[x], c) > 0)
			count++;
		x++;
	}
	return (count);
}

char	**ft_sub_redir_imput(char ***cmd, int x, int check)
{
	char	**tmp;
	char	*line;

	line = NULL;
	tmp = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (NULL);
		if (!ft_strncmp((*cmd)[x], line, ft_strlen((*cmd)[x]))
			&& ft_strlen(line) == ft_strlen((*cmd)[x]))
			break ;
		if (check == 0)
			ft_matrix_add(&tmp, line);
		free(line);
	}
	free(line);
	return (tmp);
}

int	ft_redir_imput(t_term *term, char ***cmd)
{
	int		x;
	int		fd;
	char	**tmp;

	x = 0;
	if (ft_str_nredir_count(0, *cmd, "<<") > 0)
	{
		fd = dup(1);
		while (ft_nredir_count((*cmd)[x], "<<") != 1)
			x++;
		dup2(term->fd_1, 1);
		term->i = open("temp", O_RDWR | O_CREAT, 0644);
		tmp = ft_sub_redir_imput(cmd, ++x, ft_nredir_count((*cmd)[0], "<<"));
		if (!tmp || ft_nredir_count((*cmd)[0], "<<") > 0)
			return (-1);
		dup2(term->i, 1);
		ft_matrixprint(tmp);
		ft_matrixfree(tmp);
		close (term->i);
		term->i = open("temp", O_RDONLY);
		dup2(term->i, 0);
		dup2(fd, 1);
		close(fd);
	}
	return (0);
}

size_t	ft_countredir(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == 60 || str[i] == 62)
			count++;
		i++;
	}
	return (count);
}

void	ft_checkchar(t_term *term, char *str, int i)
{
	if (str[i] == 34)
	{
		if (term->double_q == 0)
			term->double_q = 1;
		else
			term->double_q = 0;
	}
	else if (str[i] == 39)
	{
		if (term->single_q == 0)
			term->single_q = 1;
		else
			term->single_q = 0;
	}
}
