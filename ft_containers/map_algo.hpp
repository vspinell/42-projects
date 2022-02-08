/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algo.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:23:07 by vspinell          #+#    #+#             */
/*   Updated: 2022/02/07 11:25:23 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef MAP_ALGO_H
# define MAP_ALGO_H

namespace ft
{
	template<typename node_pointer>
	node_pointer next_node(node_pointer current)
	{
		if (current->parent == NULL && current->right != 0)
			return current->right;
		if ( current->parent != NULL && current->right != NULL)
		{
			current = current->right;
			while (current->parent != NULL && current->left != NULL)
				current = current->left;
			return current;
		}
		while (current->parent != NULL && current == current->parent->right)
			current = current->parent;
		if (current->parent != NULL)
		current = current->parent;
		return current;
	}
	
	template<typename node_pointer>
	node_pointer prev_node(node_pointer current)
	{
		if (current->parent == NULL && current->left != 0)
			return current->left;
		if (current->parent != NULL && current->left != NULL)
		{
			current = current->left;
			while (current->parent != NULL && current->right != NULL)
				current = current->right;
			return current;
		}
		while (current->parent != NULL && current == current->parent->left)
			current = current->parent;
		if (current->parent != NULL)
		current = current->parent;
		return current;
	}
}

# endif