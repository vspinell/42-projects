/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:28:50 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/05 15:28:54 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ft_moves(t_node *stack)
{
	t_node	*scroll;

	scroll = stack;
	while (scroll)
	{
		if (scroll->pos <= stack->len_b / 2)
		{
			scroll->movs_A = ft_movs_a(*scroll, stack->len_a);
			scroll->movs_B = scroll->pos;
			scroll->tot_movs = scroll->movs_A + scroll->movs_B;
		}
		else
		{
			scroll->movs_A = ft_movs_a(*scroll, stack->len_a);
			scroll->movs_B = stack->len_b - scroll->pos;
			scroll->tot_movs = scroll->movs_A + scroll->movs_B;
		}
		scroll = scroll->next;
	}
	scroll = stack;
	return (scroll);
}

t_stacks	ft_tot_movs(t_stacks gen)
{
	gen.head_b->movs_B = 0;
	gen.head_b->pos_a = 0;
	gen.head_b->len_a = ft_list_len(&gen.head_a);
	gen.head_b->len_b = ft_list_len(&gen.head_b);
	ft_find_Apos(&gen);
	gen.head_b = ft_moves(gen.head_b);
	return (gen);
}
