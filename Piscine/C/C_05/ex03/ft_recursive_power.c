/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:15:34 by vspinell          #+#    #+#             */
/*   Updated: 2020/11/05 15:48:49 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int nb, int power)
{
	if (power >= 0)
	{
		if (power == 0)
			nb = 1;
		else if (power > 1)
		{
			nb *= ft_recursive_power(nb, power - 1);
		}
		return (nb);
	}
	else
		return (0);
}
