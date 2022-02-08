/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:25:23 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 13:51:04 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(const char **format, t_struct *str)
{
	(*format)++;
	while (**format == '-' || **format == '0')
	{
		if (**format == '-')
		{
			str->flag_m = 1;
			(*format)++;
		}
		else if (**format == '0')
		{
			str->flag_z = 1;
			(*format)++;
		}
	}
	if (str->flag_z == 1 && str->flag_m == 1)
		str->flag_z = 0;
}

void	ft_width(const char **format, t_struct *str, va_list args)
{
	if (ft_isdigit(**format))
	{
		while (ft_isdigit(**format))
		{
			str->width = str->width * 10 + **format - '0';
			(*format)++;
		}
	}
	else if (**format == '*')
	{
		str->width = va_arg(args, int);
		if (str->width < 0)
		{
			str->width *= -1;
			str->flag_m = 1;
			str->flag_z = 0;
		}
		(*format)++;
	}
}

void	ft_precision(const char **format, t_struct *str, va_list args)
{
	if (**format == '.')
	{
		(*format)++;
		if (ft_isdigit(**format))
		{
			str->precision = 0;
			while (ft_isdigit(**format))
			{
				str->precision = str->precision * 10 + **format - '0';
				(*format)++;
			}
		}
		else if (**format == '*')
		{
			str->precision = va_arg(args, int);
			(*format)++;
		}
		else
		{
			str->precision = 0;
		}
	}
}

void	ft_type(const char **format, t_struct *str)
{
	if (**format == 'c')
		str->type = 'c';
	else if (**format == 's')
		str->type = 's';
	else if (**format == 'p')
		str->type = 'p';
	else if (**format == 'd')
		str->type = 'd';
	else if (**format == 'i')
		str->type = 'i';
	else if (**format == 'u')
		str->type = 'u';
	else if (**format == 'x')
		str->type = 'x';
	else if (**format == 'X')
		str->type = 'X';
	else if (**format == '%')
		str->type = '%';
}

void	ft_print(va_list args, t_struct *str)
{
	if (str->type == 's')
		ft_treats(va_arg(args, char*), str);
	else if (str->type == 'c')
		ft_treatc(va_arg(args, int), str);
	else if (str->type == 'd' || str->type == 'i')
		ft_treatd(va_arg(args, int), str);
	else if (str->type == 'p')
		ft_treatp(va_arg(args, size_t), str);
	else if (str->type == 'u')
		ft_treatu(va_arg(args, unsigned int), str, 10);
	else if (str->type == 'x')
		ft_treatu(va_arg(args, unsigned int), str, 16);
	else if (str->type == 'X')
		ft_treatu(va_arg(args, int), str, 16);
	else if (str->type == '%')
		ft_treatc('%', str);
}
