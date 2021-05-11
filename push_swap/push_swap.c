/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:39:58 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/05 18:40:04 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_doit2(t_stacks *gen, t_node **best, int len[2], int pos[2])
{
	if (((*best)->pos_a > len[0] / 2) && pos[0])
	{
		ft_rev_rotate(&(*gen).head_a);
		write(1, "rra\n", 4);
		pos[0]--;
	}
	else if (((*best)->pos_a <= len[0] / 2) && pos[0])
	{
		ft_rotate(&(*gen).head_a);
		write(1, "ra\n", 3);
		pos[0]--;
	}
	else if (((*best)->pos > len[1] / 2) && pos[1])
	{
		ft_rev_rotate(&(*gen).head_b);
		write(1, "rrb\n", 4);
		pos[1]--;
	}
	else if (((*best)->pos <= len[1] / 2) && pos[1])
	{
		ft_rotate(&(*gen).head_b);
		write(1, "rb\n", 3);
		pos[1]--;
	}
}

void	ft_double_rotate(t_stacks *gen)
{
	ft_rotate(&gen->head_a);
	ft_rotate(&gen->head_b);
}

t_stacks	ft_doit(t_stacks gen, t_node *best, int len[2], int pos[2])
{
	while (pos[0] || pos[1])
	{
		if ((best->pos_a <= len[0] / 2 && best->pos <= len[1] / 2)
			&& (pos[0] && pos[1]))
		{
			ft_double_rotate(&gen);
			write(1, "rr\n", 3);
			pos[0]--;
			pos[1]--;
		}
		else if ((best->pos_a > len[0] / 2 && best->pos > len[1] / 2)
			&& (pos[0] && pos[1]))
		{
			ft_rev_rotate(&gen.head_a);
			ft_rev_rotate(&gen.head_b);
			write(1, "rrr\n", 4);
			pos[0]--;
			pos[1]--;
		}
		else
			ft_doit2(&gen, &best, len, pos);
	}
	ft_push(&gen.head_a, &gen.head_b);
	write(1, "pa\n", 3);
	return (gen);
}

int	push_swap(t_stacks gen, int leng)
{
	t_node	*best;
	int		pos[2];
	int		len[2];

	if (leng <= 5)
		gen = light_push_swap(gen, leng);
	else
		gen = ft_subsequence(gen);
	gen = ft_tot_movs(gen);
	best = ft_best_move(gen.head_b);
	while (gen.head_b)
	{
		gen = ft_tot_movs(gen);
		len[0] = ft_list_len(&gen.head_a);
		len[1] = ft_list_len(&gen.head_b);
		best = ft_best_move(gen.head_b);
		pos[0] = best->movs_A;
		pos[1] = best->movs_B;
		gen = ft_doit(gen, best, len, pos);
	}
	gen.head_a = ft_reorder_stack(gen.head_a);
	exit(EXIT_SUCCESS);
}
