/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:07:01 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/29 20:21:08 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkquotes(char *str)
{
	int	i;
	int	d_q;
	int	s_q;

	i = 0;
	s_q = 0;
	d_q = 0;
	while (str && str[i])
	{
		if ((str[i] == 34 && s_q == 0) || (str[i] == 34 && d_q == 1))
			ft_activeflag(&d_q);
		else if ((str[i] == 39 && d_q == 0) || (str[i] == 39 && s_q == 1))
			ft_activeflag(&s_q);
		i++;
	}
	if (s_q == 1 || d_q == 1)
	{
		printf("SuPerBasH:~$: unexpected EOF while ");
		printf("looking for matching quotes\n");
		return (0);
	}
	return (1);
}

void	ft_parsing_init(t_term *term)
{
	term->n_cmd = 0;
	term->prompt = NULL;
	term->single_q = 0;
	term->double_q = 0;
	dup2(term->fd_0, 0);
	handle_signals(1);
}

int	ft_errors(t_term *term)
{
	if (!term->prompt)
		exit(0);
	else if (!term->prompt[0] || ft_isspace(term->prompt))
		return (1);
	add_history(term->prompt);
	if (!ft_checkquotes(term->prompt))
	{
		free(term->prompt);
		g_info_exit = 2;
		return (1);
	}
	if (ft_checkredirline(term) == -1)
	{
		free(term->prompt);
		return (1);
	}
	return (0);
}

void	ft_parsing_free(t_term *term)
{
	int	i;

	i = -1;
	while (term->cmd[++i])
		ft_matrixfree(term->cmd[i]);
	free(term->cmd);
	free(term->prompt);
}

void	ft_parsing(t_term *term)
{
	char	**tmp;
	int		i;
	int		path_line;
	int		c;

	i = 0;
	ft_parsing_init(term);
	term->prompt = readline("SuPerBasH:~$ ");
	if (ft_errors(term))
		return ;
	tmp = ft_split(term->prompt, '|');
	while (tmp[i])
		i++;
	term->n_cmd = i;
	term->cmd = (char ***)malloc(sizeof(char **) * (i + 1));
	term->cmd[i] = NULL;
	c = -1;
	while (++c < i)
		term->cmd[c] = ft_split(tmp[c], ' ');
	path_line = ft_findpath(term, "PATH=");
	ft_pipeline(term, path_line);
	ft_matrixfree(tmp);
	ft_parsing_free(term);
}
