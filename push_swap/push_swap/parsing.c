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

t_node  *ft_stack(int count, char **arguments)
{
    t_node *head;
    int i;
    char **arg;
    int j;

    head = 0;
    i = 0;
    if (count == 1)
        return (0);
    while (--count)
    {
        j = 0;
        arg = ft_split(arguments[++i], ' ');
        while (arg[j])
        {
            if (!ft_check_str(arg[j]))
              {
                  write(1, "Error\n", 6);
                  exit(EXIT_FAILURE);
              }
            t_node *new;
            new = malloc(sizeof(t_node));
            if (!new)
            {
              write(1, "Error\n", 6);
              exit(EXIT_FAILURE);
            }
            new->num = ft_atoi(arg[j++]); //cambia con arg[j++]
            free(arg[j - 1]);
            new->next = 0;
            new->prev = 0;
            new->pos = 0;
            new->flags = 0;
            if (head == 0)
                head = new;
            else
            {
                t_node *last = head;
                while (last->next != 0)
                    last = last->next;
                new->prev = last;
                last->next = new;
            }
        }
            free(arg);
    }
    arg = 0;
    return (head);
}
