/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:06:55 by vspinell          #+#    #+#             */
/*   Updated: 2020/11/05 15:14:55 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int base;

	base = nb;
	if (power >= 0)
	{
		if (power == 0)
			nb = 1;
		else
		{
			while (power > 1)
			{
				nb *= base;
				power--;
			}
		}
		return (nb);
	}
	else
		return (0);
}
