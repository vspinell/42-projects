/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reminders2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:52:16 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 14:37:08 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_check(t_struct *str)
{
	if (!(str->type))
		return (-1);
	if (str->flag_z == 1 && ((str->type == 'c') || (str->type == 's')))
		return (-1);
	return (1);
}

void		ft_putchar(char c, t_struct *str)
{
	write(1, &c, 1);
	str->counter += 1;
}

int			ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void		ft_piszero(t_struct *str)
{
	str->s = ft_strjoin("0x", str->s);
	str->width -= 2;
}
