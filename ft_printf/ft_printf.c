/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:21:44 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 13:57:09 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_struct(t_struct *str)
{
	str->flag_z = 0;
	str->flag_m = 0;
	str->width = 0;
	str->precision = -1;
	str->type = 0;
}

int		ft_pharse(const char *format, t_struct str, va_list args)
{
	while (*format)
	{
		if (*format == '%')
		{
			ft_init_struct(&str);
			ft_flags(&format, &str);
			ft_width(&format, &str, args);
			ft_precision(&format, &str, args);
			ft_type(&format, &str);
			if (ft_check(&str) == -1)
				return (-1);
			ft_print(args, &str);
		}
		else
			ft_putchar(*format, &str);
		format++;
	}
	return (str.counter);
}

int		ft_printf(const char *format, ...)
{
	t_struct	str;
	int			i;
	va_list		args;

	va_start(args, format);
	str.counter = 0;
	i = ft_pharse(format, str, args);
	va_end(args);
	return (i);
}
