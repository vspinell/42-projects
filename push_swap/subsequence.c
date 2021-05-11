/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:22:10 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/16 18:31:58 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ft_put_flags(t_node *stack_a)
{
	int		len;
	t_node	*browse;
	t_node	*jump_next;

	len = ft_list_len(&stack_a);
	if (len == -1)
		return (0);
	stack_a = ft_init_flags(stack_a);
	jump_next = stack_a;
	while (jump_next->next)
	{
		browse = jump_next->next;
		while (browse)
		{
			if (jump_next->flags == browse->flags
				&& jump_next->num < browse->num)
				browse->flags++;
			browse = browse->next;
		}
		jump_next = jump_next->next;
	}
	browse = stack_a;
	return (browse);
}

int	ft_max_flag(t_node *stack)
{
	t_node	*scroll;
	int		max_flag;

	max_flag = 1;
	scroll = stack;
	while (scroll->next)
	{
		if (scroll->next->flags > max_flag)
			max_flag = scroll->next->flags;
		scroll = scroll->next;
	}
	return (max_flag);
}

t_node	*ft_put_stars(t_node *head_a, int max_flag)
{
	t_node	*tmp;
	t_node	*last;

	last = head_a;
	while (last->next)
		last = last->next;
	while (max_flag)
	{
		tmp = last;
		while (tmp)
		{
			if (tmp->flags == max_flag)
			{
				tmp->star = 1;
				last = tmp;
				break ;
			}
			tmp = tmp->prev;
		}
		max_flag--;
	}
	tmp = head_a;
	return (tmp);
}

t_stacks	ft_subsequence(t_stacks gen)
{
	int		len;
	int		max_flag;

	gen.head_b = 0;
	gen.head_a = ft_put_flags(gen.head_a);
	max_flag = ft_max_flag(gen.head_a);
	gen.head_a = ft_put_stars(gen.head_a, max_flag);
	len = ft_list_len(&gen.head_a);
	while (len--)
	{
		 if (gen.head_a->star == 0)
		{
			ft_push(&gen.head_b, &gen.head_a);
			write(1, "pb\n", 3);
		}
		else
		{
			ft_rotate(&gen.head_a);
			write(1, "ra\n", 3);
		}
	}
	return (gen);
}

int	ft_min_numb(t_node *stack)
{
	t_node	*scroll;
	int		min;

	scroll = stack;
	min = stack->num;
	while (scroll->next)
	{
		if (scroll->next->num < min)
			min = scroll->next->num;
		scroll = scroll->next;
	}
	return (min);
}
