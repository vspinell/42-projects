/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:38:16 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 10:45:14 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_env(char **cmd)
{
	int	i;
	int	y;

	y = 0;
	while (cmd && cmd[y])
	{
		i = ft_strchr(cmd[y], '=');
		if (i > 0 && ft_isprint(cmd[y][i - 1]) && ft_isprint(cmd[y][i + 1]))
			y++;
		else
			return (y);
	}
	return (-1);
}

int	handler_env2(t_term *term, char **old_tmp, char **new_tmp)
{
	t_list	*tmp;

	tmp = term->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->old_word, *old_tmp, ft_strlen(*old_tmp)) && \
		tmp->old_word[ft_strlen(*old_tmp)] == '\0' && \
		(*old_tmp)[ft_strlen(*old_tmp)] == '\0')
		{
			free(tmp->new_word);
			tmp->new_word = ft_strdup(*new_tmp);
			tmp->new_word[ft_strlen(*new_tmp)] = '\0';
			free(*old_tmp);
			free(*new_tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstnew(*old_tmp, *new_tmp);
	ft_lstadd_back(&term->env, tmp);
	return (0);
}

void	handler_env3(char **old_tmp, char **new_tmp, char *cmd, int i)
{
	*old_tmp = malloc(sizeof(char) * (i + 1));
	ft_memcpy(*old_tmp, cmd, i);
	(*old_tmp)[i] = '\0';
	*new_tmp = malloc(sizeof(char) * (ft_strlen(cmd) - i));
	ft_memcpy(*new_tmp, cmd + i + 1, ft_strlen(cmd) - i);
	(*new_tmp)[ft_strlen(*new_tmp)] = '\0';
}

int	handler_env(t_term *term, char **cmd_d, int pos)
{
	int		i;
	char	*old_tmp;
	char	*new_tmp;
	char	*cmd;

	if (pos > 0 && (ft_control_env(term->cmd[pos]) == -1))
		return (3);
	handler_dollar(term, cmd_d);
	cmd = *cmd_d;
	i = ft_strchr(cmd, '=');
	if (i > 0 && ft_isprint(cmd[i - 1]) && ft_isprint(cmd[i + 1]))
	{
		if (pos != -1 && (ft_control_env(term->cmd[pos]) != -1))
			return (2);
		handler_env3(&old_tmp, &new_tmp, cmd, i);
		if (handler_env2(term, &old_tmp, &new_tmp))
			return (1);
		free(old_tmp);
		free(new_tmp);
		return (1);
	}	
	return (0);
}

unsigned int	numbletter_orig(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\0')
			return (i);
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			return (i + 1);
		i++;
	}
	return (i);
}
