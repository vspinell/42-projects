/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_dollar2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:45:48 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 10:46:10 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handler_dollar_sing(t_term *term, char c)
{
	if (c == 39 && term->double_q == 0)
	{
		if (term->single_q == 0)
		{
			term->single_q = 1;
			return (1);
		}
		else
		{
			term->single_q = 0;
			return (1);
		}
	}
	return (0);
}

int	handler_dollar_dou(t_term *term, char c)
{
	if (c == '"' && term->single_q == 0)
	{
		if (term->double_q == 0)
		{
			term->double_q = 1;
			return (1);
		}
		else
		{
			term->double_q = 0;
			return (1);
		}
	}
	return (0);
}

int	handler_dollar2(t_term *term, char **cmd, int c, int i)
{
	while (++c < i)
	{
		if (handler_dollar_dou(term, (*cmd)[c]))
			continue ;
		if (handler_dollar_sing(term, (*cmd)[c]))
			continue ;
	}
	return (c);
}

void	handler_dollar_qm(t_term *term, char **cmd, int i)
{
	t_list	*tmp;

	tmp = term->env;
	if ((*cmd)[i + 1] == '?' && (*cmd)[i + 2] == '\0')
	{
		free(tmp->new_word);
		tmp->new_word = ft_itoa(g_info_exit);
	}		
}
