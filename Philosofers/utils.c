/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:43:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/09/13 17:17:01 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int			sign;
	int			i;
	long int	r;

	sign = 1;
	i = 0;
	r = 0;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			return (ft_error("Error: Invalid number format"));
	}
	if (ft_isdigit(str[i]))
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			r = r * 10 + (str[i++] - '0');
			if ((r * sign) < -2147483648 || (r * sign) > 2147483647)
				ft_error("Error: Integer Overflow");
		}
		return ((int)(r * sign));
	}
	if (!ft_isdigit(str[i]))
		ft_error("Error: Invalid number format");
	return (0);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}
