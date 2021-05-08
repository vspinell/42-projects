/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:01:38 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/05 17:01:44 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ft_best_move(t_node *stack)
{
	t_node	*buff;

	if (!stack)
		return (0);
	buff = stack;
	while (stack)
	{
		if (stack->tot_movs < buff->tot_movs)
			buff = stack;
		stack = stack->next;
	}
	return (buff);
}

t_node	*ft_findpos(t_node *stackA, int position)
{
	t_node	*buff;

	buff = stackA;
	while (buff)
	{
		if (buff->pos == position)
			return (buff);
		buff = buff->next;
	}
	return (0);
}

int	ft_refreshpos(t_node *head, t_node *best)
{
	int	len;

	len = ft_list_len(&head);
	while (head)
	{
		if (head == best)
			return (head->pos);
		head = head->next;
	}
	return (0);
}

t_node	*ft_min_stackA(t_node *head)
{
	t_node	*buff;
	int		len;

	buff = head;
	len = ft_list_len(&head);
	while (head)
	{
		if (head->num < buff->num)
			buff = head;
		head = head->next;
	}
	buff->len_a = len;
	return (buff);
}

t_node	*ft_reorder_stack(t_node *head_a)
{
	t_node	*min;

	min = ft_min_stackA(head_a);
	if (min->pos <= min->len_a)
	{
		while (head_a->num != min->num)
		{
			ft_rotate(&head_a);
			write (1, "ra\n", 3);
		}
	}
	else
	{
		while (head_a->num != min->num)
		{
			ft_rev_rotate(&head_a);
			write (1, "rra\n", 4);
		}
	}
	return (head_a);
}
