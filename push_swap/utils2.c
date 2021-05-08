/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:51:08 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/15 10:17:18 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	long int	r;

	sign = 1;
	i = 0;
	r = 0;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_isdigit(str[i]))
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			r = r * 10 + (str[i] - '0');
			if ((r * sign) < -2147483648 || (r * sign) > 2147483647)
			{
				write(1, "Error\n", 6);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		return (int)(r * sign);
	}
	else
		return (-1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_check_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}
