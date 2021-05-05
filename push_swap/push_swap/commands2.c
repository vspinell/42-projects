
#include "push_swap.h"

int ft_swap(t_node **head)
{
    int i;
    if (!*head || !(*head)->next)
        return (1);
    i = (*head)->num;
    (*head)->num = (*head)->next->num;
    (*head)->next->num = i;
    /*t_node *node3;
    t_node *node2;

    node2 = *head;
    *head = (*head)->next;
    node3 = (*head)->next;
    (*head)->next = node2;
    node2->next = node3;*/

    //stampa

    t_node *stamp = *head;
        puts("dentro la funziuone");
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
    puts("");
    return (1);
}

int ft_rotate(t_node **head)
{
    t_node *new;
    t_node *last;
    t_node *first;

    if (!*head || !(*head)->next)
        return (1);
    first = *head; //tengo la posizione del primo
    new = malloc(sizeof(t_node));
    if (!new)
        return (0);
    //definisco alcuni elementi del nodo
    new->next = 0;
    new->num = first->num;
    *head = (*head)->next; //posiziono la testa al 2o nodo
    last = *head;
    while (last->next)
        last = last->next;
    last->next = new;
    new->prev = last;
    free(first);

    //stampa

    // t_node *stamp = *head;
    // while (stamp)
    // {
    //     printf("[%d] ", stamp->num);
    //     stamp = stamp->next;
    // }
    // puts("");
    return (1);
}

int ft_rev_rotate(t_node **head)
{
    t_node *first;
    t_node *last;
    t_node *tmp;

    if (!*head || !(*head)->next)
        return (1);
    first = malloc(sizeof(t_node));
    if(!first)
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

    //stampa

    // t_node *stamp = *head;
    // while (stamp)
    // {
    //     printf("[%d] ", stamp->num);
    //     stamp = stamp->next;
    // }
    // puts("");
    return (1);
}

int ft_push(t_node **dst, t_node **src)
{
    t_node *new;
    t_node *erase;

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
    erase = *src;
    *src = (*src)->next;
    free(erase);
    //stampa

    /*puts("stack B");
    t_node *stamp = *src;
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
    printf("\n");
    puts("stack A");
    t_node *stamp2 = *dst;
    while (stamp2)
    {
        printf("%d ", stamp2->num);
        stamp2 = stamp2->next;
    }
    printf("\n");*/
    return (1);
}