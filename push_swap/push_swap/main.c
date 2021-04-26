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

    init_a.head_a = ft_stack(ac, av);

    t_node *stamp = init_a.head_a;
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
}