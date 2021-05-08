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

int main(int ac, char **av)
{
    t_stacks init_a;
    int len;

    init_a.head_a = ft_stack(ac, av);
    len = ft_list_len(&init_a.head_a);
    if (len == 1)
        exit(EXIT_SUCCESS);
    else if (len == 2)
	{
		if (init_a.head_a->num > init_a.head_a->next->num)
		{
			ft_swap(&init_a.head_a);
			write(1, "sa\n", 3);
		}
		exit(EXIT_SUCCESS);
	}
    /*if (len <= 5)
        light_push_swap(init_a, len);
    else*/
        push_swap(init_a, len);
    /*t_node *stamp = init_a.head_a;
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }*/
}