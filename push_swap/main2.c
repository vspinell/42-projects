/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:56:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/26 15:56:52 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stacks	init_a;
	int			len;

	init_a.head_a = ft_stack(ac, av);
	len = ft_list_len(&init_a.head_a);
	if (len == 1 || ac == 1)
		exit(EXIT_SUCCESS);
	ft_check_doubles(init_a.head_a);
	if (len == 2)
	{
		if (init_a.head_a->num > init_a.head_a->next->num)
		{
			ft_swap(&init_a.head_a);
			write(1, "sa\n", 3);
		}
		exit(EXIT_SUCCESS);
	}
	else if (len == 3)
	{
		init_a = light_push_swap(init_a, len);
		exit(EXIT_SUCCESS);
	}
	if (ft_result(init_a.head_a) == 1)
		exit (EXIT_SUCCESS);
	push_swap(init_a, len);
}
