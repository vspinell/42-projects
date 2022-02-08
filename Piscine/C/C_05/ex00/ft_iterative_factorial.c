/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:48:58 by vspinell          #+#    #+#             */
/*   Updated: 2020/11/05 11:27:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int prev;

	prev = nb - 1;
	if (nb < 0)
		return (0);
	if (nb == 0)
		nb = 1;
	while (prev > 0)
	{
		nb *= prev;
		prev--;
	}
	return (nb);
}
