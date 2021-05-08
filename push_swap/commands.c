
#include "checker.h"

int ft_swap(t_data **head)
{
    int i;
    if (!*head || !(*head)->next)
        return (1);
    i = (*head)->num;
    (*head)->num = (*head)->next->num;
    (*head)->next->num = i;
    /*t_data *node3;
    t_data *node2;

    node2 = *head;
    *head = (*head)->next;
    node3 = (*head)->next;
    (*head)->next = node2;
    node2->next = node3;*/

    //stampa

    /*t_data *stamp = *head;
        puts("dentro la funziuone");
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
    puts("");*/
    return (1);
}

int ft_rotate(t_data **head)
{
    t_data *new;
    t_data *last;
    t_data *first;

    if (!*head || !(*head)->next)
        return (1);
    first = *head; //tengo la posizione del primo
    new = malloc(sizeof(t_data));
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

    /*t_data *stamp = *head;
    while (stamp)
    {
        printf("[%d] ", stamp->num);
        stamp = stamp->next;
    }
    puts("");*/
    return (1);
}

int ft_rev_rotate(t_data **head)
{
    t_data *first;
    t_data *last;
    t_data *tmp;

    if (!*head || !(*head)->next)
        return (1);
    first = malloc(sizeof(t_data));
    if(!first)
        return (0);
    last = *head;
    while (last->next)
    last = last->next;
    //definisco elementi del nodo
    first->next = *head;
    first->prev = 0;
    first->num = last->num;
    //riassegno la fine e l'inizio
    tmp = last;
    tmp = tmp->prev;
    tmp->next = 0;
    free(last);
    //last = last->prev;
    //last->next = 0;
    //free(last->next);
    //last->next = 0;
    (*head)->prev = first;
    *head = first;

    //stampa

    /*t_data *stamp = *head;
    while (stamp)
    {
        printf("[%d] ", stamp->num);
        stamp = stamp->next;
    }
    puts("");*/
    return (1);
}

int ft_push(t_data **dst, t_data **src)
{
    t_data *new;
    t_data *erase;

    if (!*src)
        return (1);
    new = malloc(sizeof(t_data));
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

    /*puts("stack A");
    t_data *stamp = *src;
    while (stamp)
    {
        printf("%d ", stamp->num);
        stamp = stamp->next;
    }
    puts("");
    puts("stack B");
    t_data *stamp2 = *dst;
    while (stamp2)
    {
        printf("%d ", stamp2->num);
        stamp2 = stamp2->next;
    }
    puts("");*/
    return (1);
}
