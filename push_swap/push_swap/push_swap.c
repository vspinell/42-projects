

#include "push_swap.h"

int push_swap(t_stacks gen)
{
    int ret;

    ret = 1;
    gen.count = 0;
    gen = ft_subsequence(gen);

//stampo
   t_node *stamp_a = gen.head_a;
    puts("stack A content");
    while (stamp_a)
    {
        printf("%d\n", stamp_a->num);
        stamp_a = stamp_a->next;
    }
    
    t_node *stamp_b = gen.head_b;
    puts("stack B content");
    while (stamp_b)
    {
        printf("%d\n", stamp_b->num);
        stamp_b = stamp_b->next;
    }
    return (ret);
}