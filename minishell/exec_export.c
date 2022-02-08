/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:42:12 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/26 15:49:35 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export3(char **rebuild, t_list *tmp)
{
	int	len_norme;
	int	len2_norme;

	ft_memcpy(*rebuild, tmp->old_word, ft_strlen(tmp->old_word));
	ft_memcpy(*rebuild + ft_strlen(tmp->old_word), "=", 1);
	len_norme = ft_strlen(tmp->old_word);
	len2_norme = ft_strlen(tmp->new_word);
	ft_memcpy(*rebuild + len_norme + 1, tmp->new_word, len2_norme);
	(*rebuild)[len_norme + 1 + ft_strlen(tmp->new_word)] = '\0';
}

void	ft_export2(t_term *term, char **cmd)
{
	t_list	*tmp;
	char	*rebuild;

	tmp = term->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->old_word, cmd[1], ft_strlen(tmp->old_word)) && \
		tmp->old_word[ft_strlen(tmp->old_word)] == '\0' && \
		cmd[1][ft_strlen(tmp->old_word)] == '\0')
		{
			rebuild = malloc(sizeof(char) * (ft_strlen(tmp->old_word) \
			+ ft_strlen(tmp->new_word) + 2));
			ft_export3(&rebuild, tmp);
			ft_matrix_remove_w(term, cmd[1], '=', 1);
			ft_matrix_add(&term->info.env_copy, rebuild);
			free(rebuild);
		}
		tmp = tmp->next;
	}
}

void	ft_export(t_term *term, char **cmd)
{
	int		i;

	i = -1;
	if (!cmd[1])
	{
		while (term->info.env_copy[++i])
			printf("declare -x %s\n", term->info.env_copy[i]);
	}
	else if (handler_env(term, &cmd[1], -1))
	{
		ft_matrix_remove_w(term, cmd[1], '=', 0);
		ft_matrix_add(&term->info.env_copy, cmd[1]);
	}
	else
		ft_export2(term, cmd);
}
