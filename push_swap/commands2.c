/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:55:55 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/10 12:55:58 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_swap(t_node **head)
{
	int	i;

	if (!*head || !(*head)->next)
		return (1);
	i = (*head)->num;
	(*head)->num = (*head)->next->num;
	(*head)->next->num = i;
	return (1);
}

int	ft_rotate(t_node **head)
{
	t_node	*new;
	t_node	*last;
	t_node	*first;

	if (!*head || !(*head)->next)
		return (1);
	first = *head;
	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->next = 0;
	new->num = first->num;
	*head = (*head)->next;
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	free(first);
	return (1);
}

int	ft_rev_rotate(t_node **head)
{
	t_node	*first;
	t_node	*last;
	t_node	*tmp;

	if (!*head || !(*head)->next)
		return (1);
	first = malloc(sizeof(t_node));
	if (!first)
		return (0);
	last = *head;
	while (last->next)
		last = last->next;
	first->next = *head;
	first->prev = 0;
	first->num = last->num;
	tmp = last;
	tmp = tmp->prev;
	tmp->next = 0;
	free(last);
	(*head)->prev = first;
	*head = first;
	return (1);
}

void	ft_erase(t_node ***src)
{
	t_node	*erase;

	erase = **src;
	**src = (**src)->next;
	free(erase);
}

int	ft_push(t_node **dst, t_node **src)
{
	t_node	*new;

	if (!*src)
		return (1);
	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	if (*dst == 0)
	{
		new->num = (*src)->num;
		new->next = 0;
		new->prev = 0;
		*dst = new;
	}
	else
	{
		new->num = (*src)->num;
		new->next = *dst;
		(*dst)->prev = new;
		(*dst) = new;
		(*dst)->prev = 0;
	}
	ft_erase(&src);
	return (1);
}
