/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:48:14 by francesco         #+#    #+#             */
/*   Updated: 2021/10/29 20:30:24 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (str[i] == '-')
	{
		if (str[i + 1] == 'n')
			flag = 1;
		i++;
	}
	while (str[i + 1] && str[i] == 'n')
		i++;
	if (str[i] != 'n' || flag == 0)
		return (0);
	return (1);
}

void	ft_exec_echo2(char **cmd, int i)
{
	if (i == (ft_matrixlen(cmd) - 1))
	{
		ft_putstr_fd(cmd[i], 1);
		write(1, "\n", 1);
	}
	else
	{
		ft_putstr_fd(cmd[i], 1);
		write(1, " ", 1);
	}
}

void	ft_exec_echo3(char **cmd, int i)
{
	if (i == (ft_matrixlen(cmd) - 1))
		ft_putstr_fd(cmd[i], 1);
	else
	{
		ft_putstr_fd(cmd[i], 1);
		write(1, " ", 1);
	}
}

void	ft_exec_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
		write(1, "\n", 1);
	while (cmd[i])
	{
		if (check_option(cmd[1]) == 1)
		{
			if (!cmd[2])
				return ;
			while (check_option(cmd[i]) == 1)
			{
				if (check_option(cmd[i - 1]) == 0 && i != 1)
					break ;
				i++;
			}
			ft_exec_echo3(cmd, i);
		}
		else
			ft_exec_echo2(cmd, i);
		i++;
	}
}
