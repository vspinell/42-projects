/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:57:23 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/26 15:57:26 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ft_newnode(char *arg)
{
	t_node	*new;

	if (!ft_check_str(arg))
	{
		write(1, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	new = malloc(sizeof(t_node));
	if (!new)
	{
		write(1, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	new->num = ft_atoi(arg);
	free(arg);
	new->next = 0;
	new->prev = 0;
	new->pos = 0;
	new->flags = 0;
	new->star = 0;
	new->pos_a = 0;
	return (new);
}

t_node	*ft_add_back(t_node *new, t_node *head)
{
	t_node	*last;

	last = head;
	while (last->next != 0)
		last = last->next;
	new->prev = last;
	last->next = new;
	return (new);
}

void	ft_error(void)
{
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

t_node	*ft_stack(int count, char **arguments)
{
	t_node	*head;
	t_node	*new;
	int		i[2];
	char	**arg;

	head = 0;
	i[0] = 0;
	if (count == 1)
		return (0);
	while (--count)
	{
		i[1] = 0;
		arg = ft_split(arguments[++i[0]], ' ');
		while (arg[i[1]])
		{
			new = ft_newnode(arg[i[1]++]);
			if (head == 0)
				head = new;
			else
				new = ft_add_back(new, head);
		}
		free(arg);
	}
	arg = 0;
	return (head);
}
