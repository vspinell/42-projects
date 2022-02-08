/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:14:57 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 14:04:46 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	uploads(t_struct *str)
{
	int		i;
	char	*p;
	int		count;

	count = ft_strlen(str->s) + 1;
	i = 0;
	if (!(p = malloc(count + 1)))
		return ;
	p[i++] = '-';
	while (--count)
	{
		p[i] = str->s[i - 1];
		i++;
	}
	p[i] = 0;
	str->s = p;
}

void	ft_elseisneg(t_struct *str, int len)
{
	int i;

	i = 0;
	if (str->width > len)
	{
		if (str->flag_z == 1)
		{
			ft_putchar('-', str);
			ft_pad(str->width - (len + 1), str);
		}
		else
		{
			uploads(str);
			ft_pad(str->width - ft_strlen(str->s), str);
		}
	}
	else
		ft_putchar('-', str);
}

void	ft_isneg(int c, t_struct *str, int len)
{
	int		i;
	char	*s;
	int		count;

	count = ft_strlen(str->s) + 1;
	i = 0;
	if (c < 0)
	{
		if (str->precision > len)
		{
			str->flag_z = 0;
			if (!(s = malloc(count + 1)))
				return ;
			s[i++] = '-';
			while (--count)
			{
				s[i] = str->s[i - 1];
				i++;
			}
			s[i] = 0;
			str->s = s;
		}
		else
			ft_elseisneg(str, len);
	}
}

void	ft_toupper(t_struct *str)
{
	int i;

	i = 0;
	while (str->s[i])
	{
		if (str->s[i] >= 97 && str->s[i] <= 122)
			str->s[i] -= 32;
		i++;
	}
}
