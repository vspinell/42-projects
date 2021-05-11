/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:52:38 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/10 15:52:40 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_data	*ft_newnode(char *arg)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
	{
		write(1, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	new->num = ft_atoi(arg);
	free(arg);
	new->next = 0;
	new->prev = 0;
	return (new);
}

t_data	*ft_add_back(t_data *new, t_data *head)
{
	t_data	*last;

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

void	ft_chekkalo(char *str)
{
	if (!ft_check_str(str))
		ft_error();
}

t_data	*ft_stack(int count, char **arguments)
{
	t_data	*head;
	t_data	*new;
	int		i[2];
	char	**arg;

	head = 0;
	i[0] = 0;
	while (--count)
	{
		i[1] = 0;
		arg = ft_split(arguments[++i[0]], ' ');
		while (arg[i[1]])
		{
			ft_chekkalo(arg[i[1]]);
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
