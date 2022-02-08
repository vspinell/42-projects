/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reminders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:11:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 14:03:18 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_extrau(int n, t_struct *str, int len)
{
	if (n == 0 && str->precision == 0)
	{
		str->s = "";
		len -= 1;
	}
	return (len);
}

void	ft_putspace(int quant, t_struct *str)
{
	while (quant--)
		ft_putchar(' ', str);
}

void	ft_putzero(int quant, t_struct *str)
{
	while (quant--)
		ft_putchar('0', str);
}

void	ft_treatc(char c, t_struct *str)
{
	if (str->width > 1)
	{
		if (str->type == '%' && str->flag_z == 1)
		{
			ft_putzero(str->width - 1, str);
			ft_putchar(c, str);
		}
		else if (str->flag_m)
		{
			ft_putchar(c, str);
			ft_putspace(str->width - 1, str);
		}
		else
		{
			ft_putspace(str->width - 1, str);
			ft_putchar(c, str);
		}
	}
	else
		ft_putchar(c, str);
}
