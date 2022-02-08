/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 11:15:48 by francesco         #+#    #+#             */
/*   Updated: 2021/10/29 20:20:30 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_info_exit;

void	ft_fillstruct(int argc, char **argv, char **env, t_term *term)
{
	term->info.argc = argc;
	term->info.argv = argv;
	ft_matrixcopy(&term->info.env_copy, env);
}

void	ft_info_list2(t_term *term, char **tmp, char **tmp1)
{
	char	*norme;

	norme = NULL;
	norme = ft_itoa(g_info_exit);
	term->env = ft_lstnew("?", norme);
	free(norme);
	*tmp = NULL;
	*tmp1 = NULL;
}

void	ft_info_list(t_term *term)
{
	char		*tmp;
	char		*tmp1;
	t_list		*new;
	int			i;
	int			y;

	i = -1;
	y = 0;
	ft_info_list2(term, &tmp, &tmp1);
	while (term->info.env_copy[++i])
	{
		y = ft_strchr(term->info.env_copy[i], '=');
		tmp = malloc(sizeof(char) * (y + 1));
		ft_memcpy(tmp, term->info.env_copy[i], y);
		tmp[y] = '\0';
		tmp1 = malloc(sizeof(char) * (ft_strlen(term->info.env_copy[i]) - y));
		ft_memcpy(tmp1, term->info.env_copy[i] + y + 1,
			ft_strlen(term->info.env_copy[i]) - y);
		tmp1[ft_strlen(tmp1)] = '\0';
		new = ft_lstnew(tmp, tmp1);
		ft_lstadd_back(&term->env, new);
		free(tmp);
		free(tmp1);
	}
}

void	ft_init(t_term *term)
{
	term->env = NULL;
	g_info_exit = 0;
	term->fd_0 = dup(0);
	term->fd_1 = dup(1);
	term->double_q = 0;
	term->single_q = 0;
	term->c_quote = 0;
	term->q_skip = 0;
	term->i = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_term	term;
	t_list	*head;

	ft_init(&term);
	ft_fillstruct(argc, argv, env, &term);
	ft_info_list(&term);
	ft_print_minishell();
	while (1)
		ft_parsing(&term);
	while (term.env)
	{
		head = term.env->next;
		free(term.env->old_word);
		free(term.env->new_word);
		free(term.env);
		term.env = head;
	}
	ft_matrixfree(term.info.env_copy);
}
