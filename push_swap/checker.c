/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:24:40 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/19 12:24:44 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ft_commands(char *line, t_head *stacks)
{
    int ret;

    ret = 1;
    if (ft_strncmp(line, "sa", ft_strlen(line)) == 0)
        ret = ft_swap(&stacks->head_a);
    else if (ft_strncmp(line, "sb", ft_strlen(line)) == 0)
        ret = ft_swap(&stacks->head_b);
    else if (ft_strncmp(line, "ss", ft_strlen(line)) == 0)
    {
        ret = ft_swap(&stacks->head_a);
        ret *= ft_swap(&stacks->head_b);
    }
    else if (ft_strncmp(line, "pa", ft_strlen(line)) == 0)
        ret = ft_push(&stacks->head_a, &stacks->head_b);
    else if (ft_strncmp(line, "pb", ft_strlen(line)) == 0)
        ret = ft_push(&stacks->head_b, &stacks->head_a);
    else if (ft_strncmp(line, "ra", ft_strlen(line)) == 0)
        ret = ft_rotate(&stacks->head_a);
    else if (ft_strncmp(line, "rb", ft_strlen(line)) == 0)
        ret = ft_rotate(&stacks->head_b);
    else if (ft_strncmp(line, "rr", ft_strlen(line)) == 0)
    {
        ret = ft_rotate(&stacks->head_a);
        ret *= ft_rotate(&stacks->head_b);
    }
     else if (ft_strncmp(line, "rra", ft_strlen(line)) == 0)
        ret = ft_rev_rotate(&stacks->head_a);
     else if (ft_strncmp(line, "rrb", ft_strlen(line)) == 0)
        ret = ft_rev_rotate(&stacks->head_b);
     else if (ft_strncmp(line, "rrr", ft_strlen(line)) == 0)
        {
            ret = ft_rev_rotate(&stacks->head_a);
            ret = ft_rev_rotate(&stacks->head_b);
        }
    else
    {
        write (1, "Error\n", 6);
        exit(EXIT_FAILURE);
    }
    return (ret);
}


int checker(t_head stacks)
{
    int ret;
    char *line;

    stacks.head_b = 0;
    ft_check_doubles(stacks.head_a);
    line = 0;
    while (1)
    {
        ret = get_next_line(&line);
        if (ret == 0)
            break;
        if (!ft_commands(line, &stacks))
            return (-1);
        free(line);
        line = NULL;
    }
    free(line);
    line = NULL;
    ft_result(&stacks);

    //----stampa per vedere che hai fatto---//

    t_data *stamp = stacks.head_a;
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
    puts("");
    return (0);
}

int ft_result(t_head *stacks)
{
    /*t_data *stamp = stacks->head_a;
    while (stamp)
    {
        printf("[%d] ", stamp->num);
        stamp = stamp->next;
    }
    puts("");*/
    if (stacks->head_a == 0)
        exit(0);
    if (stacks->head_b != 0)
    {
        write(1, "KO\n", 3);
        exit(EXIT_FAILURE);
    }
    while (stacks->head_a->next)
    {
        if (stacks->head_a->num < stacks->head_a->next->num)
        {
            stacks->head_a = stacks->head_a->next;
            free(stacks->head_a->prev);

        }
        else
        {
            write(1, "KO\n", 3);
            exit(EXIT_FAILURE);
        }
    }
    free(stacks->head_a);
    write(1, "OK\n", 3);
    exit(EXIT_SUCCESS);
    return (1);
}
