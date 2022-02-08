/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 11:51:12 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 17:49:54 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, sigint_father);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, sigquit_child);
	}
}

void	sigint_father(int sig)
{
	(void)sig;
	g_info_exit = 1;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_child(int sig)
{
	(void)sig;
	g_info_exit = 130;
	printf("\n");
}

void	sigquit_child(int sig)
{
	(void)sig;
	g_info_exit = 131;
	ft_putstr_fd("Quit: 3\n", 1);
}
