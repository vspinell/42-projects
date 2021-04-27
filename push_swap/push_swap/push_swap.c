

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
        printf("stack_pos = %d \n", (*stack)->pos);
        *stack = (*stack)->next;
    }
    *stack = head;

    puts("vediamo che cazzo ce dentro");
    t_node *stamp = *stack;
    while (stamp)
    {
        printf("indice nodo [%d]\n", (*stack)->pos);
        stamp = stamp->next;
    }
    return ((*stack)->pos + 1);
}

t_node    *ft_subsequence(t_node *stack_a)
{
    int len;

    len = ft_list_len(&stack_a);
    printf("len lista = %d\n", len);
    
    /*t_node *stamp;
    while (stamp)
    {
        printf("indice nodo [%d]\n", stack_a->pos);
        stamp = stamp->next;
    }*/
   return (stack_a); 
}   


int push_swap(t_stacks gen)
{
    int ret;

    ret = 1;
    gen.head_a = ft_subsequence(gen.head_a);
    //gen = ft_sort_stacks(gen);

//stampo
   t_node *stamp_a = gen.head_a;
    puts("stack A content");
    while (stamp_a)
    {
        printf("%d\n", stamp_a->num);
        stamp_a = stamp_a->next;
    }
    /*
    t_node *stamp_b = gen.head_b;
    puts("stack B content");
    while (stamp_b)
    {
        printf("%d\n", stamp_b->num);
        stamp_b = stamp_b->next;
    }*/
    return (ret);
}