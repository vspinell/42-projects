/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:59:10 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/27 11:40:46 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{	
	if (!*lst)
		*lst = new;
	else
	{
		new->i = ft_lstlast(*lst)->i + 1;
		ft_lstlast(*lst)->next = new;
	}	
	new->next = NULL;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstnew(char *old, char *new)
{
	t_list	*newelement;

	newelement = (t_list *)malloc(sizeof(t_list));
	newelement->i = 0;
	newelement->old_word = ft_strdup(old);
	newelement->new_word = ft_strdup(new);
	newelement->next = NULL;
	return (newelement);
}

int	ft_lstsize(t_list *lst)
{
	int	x;

	x = 0;
	while (lst)
	{
		x++;
		lst = lst->next;
	}
	return (x);
}
