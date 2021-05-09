/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:06:58 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/05 15:16:25 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max_stackA(t_node *head)
{
	int		len;
	t_node	*buff;

	buff = head;
	len = ft_list_len(&head);
	while (head)
	{
		if (head->num > buff->num)
			buff = head;
		head = head->next;
	}
	if (buff->pos == len - 1)
		return (0);
	else
		return (buff->pos + 1);
}

int	ft_pos_a(t_node *stack_a)
{
	t_node	*buff;
	t_node	*head;
	int		ret;

	head = stack_a;
	ret = 0;
	buff = 0;
	while (stack_a)
	{
		if (stack_a->star == 1 && buff ==0)
			buff = stack_a;
		else if (stack_a->star == 1 && stack_a->num < buff->num)
			buff = stack_a;
		stack_a = stack_a->next;
	}
	if (buff)
		ret = buff->pos;
	else
	{
		ret = max_stackA(head);
	}
	return (ret);
}

t_node	*ft_clean_stars(t_node *stack)
{
	t_node	*clean;

	clean = stack;
	while (clean)
	{
		clean->star = 0;
		clean = clean->next;
	}
	clean = stack;
	return (clean);
}

void	ft_find_Apos(t_stacks *gen)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = ft_clean_stars(gen->head_a);
	stack_b = gen->head_b;
	while (stack_b)
	{
		while (stack_a)
		{
			if (stack_a->num > stack_b->num)
				stack_a->star = 1;
			stack_a = stack_a->next;
		}
		stack_a = gen->head_a;
		stack_b->pos_a = ft_pos_a(stack_a);
		stack_a = ft_clean_stars(stack_a);
		stack_b = stack_b->next;
	}
	stack_b = gen->head_b;
	gen->head_b = stack_b;
}

int	ft_movs_a(t_node node, int len_A)
{
	if (node.pos_a <= (len_A / 2))
	{
		return (node.pos_a);
	}
	else
	{
		return (len_A - node.pos_a);
	}
}
