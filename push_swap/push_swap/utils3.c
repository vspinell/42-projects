#include "push_swap.h"

int ft_list_len(t_node **stack)
{
    t_node *head;
    int buff;

    head = *stack;
    buff = 0;
    while (*stack)
    {
        (*stack)->pos = 0;
        *stack = (*stack)->next;
    }
    *stack = head;
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