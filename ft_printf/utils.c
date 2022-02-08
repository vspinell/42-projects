/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:31:39 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 13:58:43 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putstr(char *s, t_struct *str)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar(s[i], str);
		i++;
	}
}

char		*ft_strjoin(char *str1, char *str2)
{
	int		i;
	char	*joined;
	int		j;

	j = 0;
	i = 0;
	if (!(joined = malloc(ft_strlen(str1) + ft_strlen(str2) + 1)))
		return (0);
	while (str1[j])
		joined[i++] = str1[j++];
	j = 0;
	while (str2[j])
		joined[i++] = str2[j++];
	joined[i] = 0;
	return (joined);
}

char		*ft_fill_width(int count, t_struct *str)
{
	char	*fill;
	int		i;

	i = 0;
	if (!(fill = malloc(count + 1)))
		return (0);
	while (count--)
	{
		if (str->flag_z == 1)
			fill[i++] = '0';
		else
			fill[i++] = 32;
	}
	fill[i] = 0;
	return (fill);
}

char		*ft_substr(char *s, int len)
{
	char	*subs;
	int		i;

	i = 0;
	if (!(subs = malloc(len + 1)))
		return (0);
	while (len-- && *s)
	{
		*subs++ = *s++;
		i++;
	}
	*subs = 0;
	return (subs - i);
}

void		ft_pad(int c, t_struct *str)
{
	char	*right;
	char	*left;

	if (str->flag_m == 1)
	{
		left = str->s;
		right = ft_fill_width(c, str);
	}
	else
	{
		left = ft_fill_width(c, str);
		right = str->s;
	}
	if (str->type == 'X')
		ft_toupper(str);
	ft_putstr(ft_strjoin(left, right), str);
}
