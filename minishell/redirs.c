/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:20:59 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/28 16:11:50 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_countredir2(char *str, t_term *term)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		ft_checkchar(term, str, i);
		if ((str[i] == 60 || str[i] == 62)
			&& (term->single_q == 0 && term->double_q == 0))
			count++;
		i++;
	}
	return (count);
}

int	ft_checkfile2(char ***cmd, int x, t_term *term)
{
	if (ft_nredir_count((*cmd)[x - 1], ">>") > 0)
	{
		ft_clearpath((*cmd)[x]);
		term->i = open((*cmd)[x], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (term->i == -1)
			return (0);
		dup2(term->i, 1);
	}
	else if (ft_nredir_count((*cmd)[x - 1], "<<") > 0)
	{
		ft_clearpath((*cmd)[x]);
		if (ft_redir_imput(term, cmd) == -1)
			return (-1);
	}
	return (1);
}

int	ft_check_file(char ***cmd, int x, t_term *term)
{
	int	ret;

	ret = 1;
	if (ft_nredir_count((*cmd)[x - 1], ">") > 0)
	{
		ft_clearpath((*cmd)[x]);
		term->i = open((*cmd)[x], O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(term->i, 1);
	}
	else if (ft_nredir_count((*cmd)[x - 1], "<") > 0)
	{
		ft_clearpath((*cmd)[x]);
		term->i = open((*cmd)[x], O_RDONLY);
		if (term->i == -1)
			ret = ft_notfound((*cmd)[x]);
		else
			dup2(term->i, 0);
	}
	else
		ret = ft_checkfile2(cmd, x, term);
	ft_matrix_remove(cmd, (*cmd)[x - 1]);
	ft_matrix_remove(cmd, (*cmd)[x - 1]);
	return (ret);
}

int	ft_handle_remaninquote(t_term *term, char ***cmd, int check, int n)
{
	int	i;

	i = 0;
	if (check != -1)
	{
		while ((*cmd)[check][i])
		{
			if ((*cmd)[check][i] == 39 || (*cmd)[check][i] == 34)
			{
				(*cmd)[check] = ft_remove_char((*cmd)[check], i);
				continue ;
			}
			if (!(*cmd)[check][i])
				break ;
			i++;
		}
	}
	i = -1;
	while (cmd && (*cmd)[++i])
	{
		if (ft_countredir2((*cmd)[i], term) > 0)
			n++;
	}
	return (n);
}

int	ft_manageredir(t_term *term, char ***cmd)
{
	int	y;
	int	n;
	int	check;

	n = 0;
	check = ft_check_specialcase(cmd);
	if (ft_countredir(term->prompt) > 0)
	{
		n = ft_handle_remaninquote(term, cmd, check, n);
		while (n--)
		{
			y = 0;
			while (ft_countredir2((*cmd)[y], term) == 0 && (*cmd)[y])
				y++;
			if (ft_check_file(cmd, y + 1, term) == -1)
				return (-1);
		}
	}
	ft_quoteclean(cmd);
	return (1);
}
