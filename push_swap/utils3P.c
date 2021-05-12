#include "push_swap.h"

int	ft_list_len(t_node **stack)
{
	t_node	*head;
	int		buff;

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
	return (buff);
}

t_node	*ft_init_flags(t_node *stack_a)
{
	t_node	*tmp;

	tmp = stack_a;
	while (tmp)
	{
		tmp->flags = 1;
		tmp = tmp->next;
	}
	tmp = stack_a;
	return (tmp);
}

int	ft_result(t_node *head_a)
{
	if (head_a == 0)
		exit(0);
	while (head_a->next)
	{
		if (head_a->num < head_a->next->num)
			head_a = head_a->next;
		else
			return (0);
	}
	return (1);
}
