/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeprocess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:30:34 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 14:35:58 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_treats(char *string, t_struct *str)
{
	int		len;
	int		count;
	char	*a;

	len = (string == (char*)0) ? 6 : ft_strlen(string);
	str->s = (string == (char*)0) ? "(null)" : string;
	a = (string == (char*)0) ? "(null)" : string;
	if (str->precision > -1)
	{
		str->s = ft_substr(a, str->precision);
		len = ft_strlen(str->s);
	}
	if (str->width > len)
	{
		count = str->width - len;
		ft_pad(count, str);
	}
	else
		ft_putstr(str->s, str);
}

void	ft_prec(int len, t_struct *str, int i)
{
	str->flag_z = 1;
	str->s = ft_strjoin(ft_fill_width(str->precision - len, str), str->s);
	str->flag_z = 0;
	if (str->type == 'X')
		ft_toupper(str);
	ft_isneg(i, str, len);
	if (str->width > len && str->precision < str->width)
		ft_pad(str->width - ft_strlen(str->s), str);
	else
	{
		if (str->type == 'X')
			ft_toupper(str);
		ft_putstr(str->s, str);
	}
}

void	ft_treatd(int n, t_struct *str)
{
	int			len;
	long int	l;

	l = (n > 0) ? n : -(long int)n;
	len = n == 0 ? 1 : ft_intlen(l, 10);
	str->s = ft_utoa(l, 10, len);
	if (n == 0 && str->precision == 0)
		len = ft_extrau(l, str, len);
	if (str->precision > len)
		ft_prec(len, str, n);
	else if (str->width > len)
	{
		if (str->precision > 0)
			str->flag_z = 0;
		if (n < 0)
			ft_isneg(n, str, len);
		else
			ft_pad(str->width - len, str);
	}
	else
	{
		ft_isneg(n, str, len);
		ft_putstr(str->s, str);
	}
}

void	ft_treatu(unsigned int n, t_struct *str, int base)
{
	int	len;

	n = (n > 0) ? n : 4294967296 + n;
	len = ft_intlen(n, base);
	str->s = ft_utoa(n, base, len);
	if (n == 0 && str->precision == 0)
	{
		str->s = "";
		len -= 1;
	}
	if (str->precision > len)
		ft_prec(len, str, n);
	else if (str->width > len)
	{
		if (str->precision > 0)
			str->flag_z = 0;
		ft_pad(str->width - len, str);
	}
	else
	{
		if (str->type == 'X')
			ft_toupper(str);
		ft_putstr(str->s, str);
	}
}

void	ft_treatp(size_t address, t_struct *str)
{
	int len;

	len = ft_intlen(address, 16);
	str->s = ft_utoa(address, 16, len);
	if (address == 0)
	{
		str->s = (str->precision == 0) ? "0x" : "0x0";
		len = ft_strlen(str->s);
		if ((str->width <= len) || (str->precision == 0 && str->width <= len))
		{
			ft_putstr(str->s, str);
			return ;
		}
	}
	if (str->width > len)
	{
		if (address != 0)
			ft_piszero(str);
		ft_pad(str->width - len, str);
	}
	else
	{
		str->s = ft_utoa(address, 16, len);
		ft_putstr(ft_strjoin("0x", str->s), str);
	}
}
