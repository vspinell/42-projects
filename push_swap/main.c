/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:24:56 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/19 12:24:59 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int ac, char **av)
{
	t_head	stacks;

	stacks.head_a = ft_stack(ac, av);
	if (checker(stacks) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	return (0);
}
