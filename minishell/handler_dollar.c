/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:38:29 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 10:48:13 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handler_dollar4(char **cmd, int i, int len_w, t_list *tmp)
{
	char	*new;
	int		norme;

	norme = ft_strlen(tmp->new_word);
	new = malloc(sizeof(char) * (ft_strlen(*cmd) + -len_w + norme + 1));
	ft_memcpy(new, *cmd, i);
	ft_memcpy(new + i, tmp->new_word, ft_strlen(tmp->new_word));
	norme = ft_strlen(*cmd + i + len_w);
	ft_memcpy(new + i + ft_strlen(tmp->new_word), *cmd + i + len_w, norme);
	new[i + ft_strlen(tmp->new_word) + ft_strlen(*cmd + i + len_w)] = '\0';
	return (new);
}

int	handler_dollar5(char **cmd, int i, t_list *tmp, int len_w)
{
	if ((*cmd)[i + 1 + ft_strlen(tmp->old_word)] == '$')
		return (numbletter_orig(*cmd + i, '$'));
	if ((*cmd)[i + 1 + ft_strlen(tmp->old_word)] == '"')
		return (numbletter_orig(*cmd + i, '"'));
	if ((*cmd)[i + 1 + ft_strlen(tmp->old_word)] == 39)
		return (numbletter_orig(*cmd + i, 39));
	return (len_w);
}

int	handler_dollar3(t_term *term, char **cmd, int i, char **new)
{
	int		len_w;
	t_list	*tmp;

	len_w = numbletter_orig(*cmd + i, ' ');
	tmp = term->env;
	while (tmp)
	{
		if (!ft_strncmp(*cmd + i + 1, tmp->old_word, ft_strlen(tmp->old_word))
			&& ((*cmd)[i + 1 + ft_strlen(tmp->old_word)] == '\0' || \
			(*cmd)[i + 1 + ft_strlen(tmp->old_word)] == ' ' || \
			(*cmd)[i + 1 + ft_strlen(tmp->old_word)] == '$' || \
			(*cmd)[i + 1 + ft_strlen(tmp->old_word)] == '"' || \
			(*cmd)[i + 1 + ft_strlen(tmp->old_word)] == 39))
		{
			len_w = handler_dollar5(cmd, i, tmp, len_w);
			*new = handler_dollar4(cmd, i, len_w, tmp);
			term->c_quote = i;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	handler_dollar_f(t_term *term, char **cmd, int i, char **new)
{
	while (i >= 0 && ft_isprint((*cmd)[i + 1]))
	{
		if (term->double_q == 1 || \
		(term->double_q == 0 && term->single_q == 0 ))
		{
			if (handler_dollar3(term, cmd, i, new) != -1)
			{
				*new = malloc(sizeof(char) * (i + 1));
				ft_memcpy(*new, *cmd, i);
				(*new)[i] = '\0';
			}
			free(*cmd);
			*cmd = *new;
		}
		else
		{
			term->q_skip++;
			term->c_quote = i;
		}
		i = ft_strchr_mod(*cmd, '$', term->q_skip);
		term->c_quote = handler_dollar2(term, cmd, term->c_quote, i);
	}	
}

void	handler_dollar(t_term *term, char **cmd)
{
	int		i;
	char	*new;

	i = ft_strchr_mod(*cmd, '$', 0);
	term->c_quote = handler_dollar2(term, cmd, -1, i);
	handler_dollar_qm(term, cmd, i);
	handler_dollar_f(term, cmd, i, &new);
	term->double_q = 0;
	term->single_q = 0;
	term->c_quote = 0;
	term->q_skip = 0;
}
