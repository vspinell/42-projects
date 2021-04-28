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

int ft_list_len(t_node **stack)
{
    t_node *head;
    int buff;

    head = *stack;
    (*stack)->pos = 0;
    buff = 0;
    while (*stack)
    {
        (*stack)->pos = (*stack)->pos + buff;
        buff++;
        *stack = (*stack)->next;
    }
    *stack = head;

    /*printf("vediamo che cazzo ce dentro\n");
    t_node *stamp = *stack;
    while (stamp)
    {
        printf("indice nodo [%d]\n", stamp->pos);
        stamp = stamp->next;
    }*/
    return (buff);
}

t_node  *ft_init_flags(t_node *stack_a)
{
    t_node *tmp;

    tmp = stack_a;
    while(tmp)
    {
        tmp->flags = 1;
        tmp = tmp->next;
    }
    tmp = stack_a;
    return (tmp);
}

t_node    *ft_put_flags(t_node *stack_a)
{
    int len;
    t_node *browse;
    t_node *jump_next;

    stack_a->len_A = ft_list_len(&stack_a);
    stack_a = ft_init_flags(stack_a);
    jump_next = stack_a;
    while(jump_next->next)
    {
        browse = jump_next->next;
        while (browse)
        {
            if (jump_next->flags == browse->flags && jump_next->num < browse->num)
                browse->flags++;
            browse = browse->next;
        }
        jump_next = jump_next->next;
    }
    browse = stack_a;
    return (browse);
}   

int ft_max_flag(t_node *stack)
{
    t_node  *scroll;
    int     max_flag;

    max_flag = 1;
    scroll = stack;
    while(scroll->next)
    {
        if(scroll->next->flags > max_flag)
            max_flag = scroll->next->flags;
        scroll = scroll->next;
    }
    return (max_flag);
}

t_node *ft_put_stars(t_node *head_a, int max_flag)
{
    t_node *tmp;
    t_node *last;
    
    //printf("[%d] THIS IS THE MAX FLAG!!!\n", max_flag);
    last = head_a;
    while (last->next)
        last = last->next;//qua vado alla fine
    //printf("ultimo numero [%d]\n", last->num);
    while(max_flag)
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

t_stacks  ft_subsequence(t_stacks gen)
{
    int len;
    int max_flag;
    t_node *last;

    //-------->(prova a riattivare alla fine) <-------

    /*gen.head_a = ft_reorder_stack(gen.head_a, gen);
    t_node *stamp = gen.head_a;
    puts("Inside the reordered strunzata");
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
    puts("");*/
    gen.head_a = ft_put_flags(gen.head_a);
    max_flag = ft_max_flag(gen.head_a);
    gen.head_a = ft_put_stars(gen.head_a, max_flag);
    //printf("len lista = %d\n", gen.head_a->len_A);

    last = gen.head_a;
    while (last->next)
        last = last->next;
    while (gen.head_a->num != last->num)
    {
        if (gen.head_a->star != 1)
                ft_push(&gen.head_b, &gen.head_a, &gen);
        else
        {
            ft_rotate(&gen.head_a, &gen);
            max_flag--;
        }
    }
    if (gen.head_a->star != 1)
            ft_push(&gen.head_b, &gen.head_a, &gen);
    if (gen.head_a->num > gen.head_a->next->num)
            ft_rotate(&gen.head_a, &gen);
    return (gen);
}

int ft_min_numb(t_node *stack)
{
    t_node  *scroll;
    int     min;

    scroll = stack;
    min = stack->num;
    while(scroll->next)
    {
        if(scroll->next->num < min)
            min = scroll->next->num;
        scroll = scroll->next;
    }
    return (min);
}

t_node *ft_reorder_stack(t_node *head_a, t_stacks gen)
{
    int     min;

    min = ft_min_numb(head_a);
    while (head_a->num != min)
        ft_rotate(&head_a, &gen);
    return (head_a);
}